using System;

namespace threads
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			new ParallelComputation().PrintFactors(123456789);
			Console.ReadLine ();
		}
	}
}
