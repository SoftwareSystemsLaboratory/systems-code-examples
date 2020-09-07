using System;
using System.Collections.Generic;
using System.Threading;

namespace threads
{
	//begin-class-ThreadedList
	public class ThreadedList<T> : IEnumerable<T>
	{
		private readonly IEnumerable<T> _list;

		public ThreadedList (IEnumerable<T> list){
			_list = list;
		}

		public IEnumerator<T> GetEnumerator ()
		{
			return new ThreadedEnumerator<T>(_list.GetEnumerator ());
		}

		System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator ()
		{
			return GetEnumerator ();
		}

		private class ThreadedEnumerator<S> : IEnumerator<S> {

			private readonly IEnumerator<S> _enumerator;
			private readonly Queue<S> _queue;
			private const int _maxQueueSize = 10;
			private readonly Thread _thread;
			private volatile bool _keepGoing = true;
			private volatile bool _finishedEnumerating = false;
			private S _current;

			public ThreadedEnumerator(IEnumerator<S> enumerator) {
				_enumerator = enumerator;
				_thread = new Thread(Enumerate);
				_thread.Start();
			}

			private void Enumerate() {
				while (_keepGoing) {
					if (_enumerator.MoveNext ()) {
						var current = _enumerator.Current;
						lock (_queue) {
							while (_queue.Count > _maxQueueSize && _keepGoing) {
								Monitor.Wait (_queue, 100);
							}
							if (_keepGoing) {
								_queue.Enqueue (current);
								Monitor.Pulse (_queue);
							}
						}
					} else {
						break;
					}
				}
				_finishedEnumerating = true;
			}

			public bool MoveNext ()
			{
				lock (_queue) {
					while (!_finishedEnumerating && _queue.Count == 0) {
						Monitor.Wait (_queue, 100);
					}
					if (_queue.Count > 0) {
						_current = _queue.Dequeue ();
						Monitor.Pulse (_queue);
						return true;
					} else {
						_current = default(S);
						return false;
					}
				}
			}

			public void Reset () {
				lock (_queue) {
					lock (_enumerator) {
						_enumerator.Reset ();
						_queue.Clear ();
					}
				}
			}

			object System.Collections.IEnumerator.Current {
				get { return _current; }
			}

			public void Dispose () {
				_keepGoing = false;
				_thread.Join ();
			}

			public S Current {
				get { return _current; }
			}
		}
	}
	//end-class-ThreadedList
}

