using System;
using System.Threading;
using System.Collections.Generic;

namespace threads
{
	//begin-class-ParallelComputation
	public class ParallelComputationWorkItem {
		public readonly long LowerBound;
		public readonly long UpperBound;
		public readonly long Number;
		public readonly ICollection<long> Divisors;
		public ParallelComputationWorkItem(long lower, long upper, long number, ICollection<long> divisors) {
			LowerBound = lower;
			UpperBound = upper;
			Number = number;
			Divisors = divisors;
		}
	}

	public class ParallelComputation {

		public void PrintFactors(long number) {
			var threads = new List<Thread>();
			var divisors = new List<long> ();
			var cpuCount = Environment.ProcessorCount;
			long lower = 1;
			for (var i = 0; i < cpuCount; i++) {
				var thread = new Thread (Worker);
				var upper = lower + (number / cpuCount);
				thread.Start(new ParallelComputationWorkItem(lower, upper, number, divisors));
				threads.Add (thread);
				lower = upper;
			}
			foreach (var thread in threads) {
				thread.Join ();
			}
			Console.WriteLine ("Divisors - ");
			foreach (var divisor in divisors) {
				Console.WriteLine (divisor);
			}
		}

		private void Worker(object args) {
			var workItem = (ParallelComputationWorkItem)args;
			for (var i = workItem.LowerBound; i < workItem.UpperBound; i++) {
				if (workItem.Number % i == 0) {
					lock (workItem.Divisors) {
						workItem.Divisors.Add (i);
					}
				}
			}
		}
	}
	//end-class-ParallelComputation
}

