using System;
using System.Threading;
using System.Collections.Generic;

namespace threads
{
	//begin-class-BoundBuffer
	public class BoundBuffer<T> {
		private readonly Semaphore _full;
		private readonly Semaphore _empty;
		private readonly Semaphore _lock;
		private readonly Queue<T> _queue;

		public BoundBuffer (int maxCount) {
			_empty = new Semaphore (maxCount, maxCount);
			_full = new Semaphore (0, maxCount);
			_lock = new Semaphore (1, 1);
			_queue = new Queue<T> ();
		}

		public void Enqueue(T item) {
			_empty.WaitOne ();
			_lock.WaitOne ();
			_queue.Enqueue (item);
			_lock.Release (1);
			_full.Release (1);
		}

		public T Dequeue() {
			_full.WaitOne ();
			_lock.WaitOne ();
			var item = _queue.Dequeue ();
			_lock.Release(1);
			_empty.Release(1);
			return item;
		}
	}
	//end-class-BoundBuffer
}

