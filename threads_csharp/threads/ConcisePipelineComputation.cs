using System;
using System.IO;
using System.IO.Compression;
using System.Threading;
using System.Collections.Generic;

namespace threads
{
	//begin-class-ConcisePipelineComputation
	public class ConcisePipelineComputation
	{
		public ConcisePipelineComputation () {
		}

		public void PerformCompression() {
			var fileBlocks = new ThreadedList<byte[]>(FileReader());
			var compressedBlocks = new ThreadedList<byte[]> (Compression(fileBlocks));
			FileWriter (compressedBlocks);
		}

		private IEnumerable<byte[]> FileReader() {
			using (var stream = new FileStream("file.txt", FileMode.Open, FileAccess.Read)) {
				int len;
				var buffer = new byte[1024];
				while ((len = stream.Read(buffer, 0, buffer.Length)) > 0) {
					if (len != buffer.Length) {
						Array.Resize (ref buffer, len);
					}
					yield return buffer;
				}
			}
		}
		
		private IEnumerable<byte[]> Compression(IEnumerable<byte[]> readBuffer) {
			foreach (var buffer in readBuffer) {
				yield return Compress (buffer);
			}
		}

		private static byte[] Compress(byte[] data) {
			var memStream = new MemoryStream ();
			using(var compressionStream = new GZipStream(memStream, CompressionMode.Compress)) {
				compressionStream.Write(data, 0, data.Length);
			}
			return memStream.ToArray ();
		}

		private void FileWriter(IEnumerable<byte[]> compressedBuffer) {
			using (var stream = new FileStream("file.gz", FileMode.OpenOrCreate, FileAccess.Write)) {
				foreach (var buffer in compressedBuffer) {
					stream.Write (buffer, 0, buffer.Length);
				}
			}
		}
	}
	//end-class-ConcisePipelineComputation
}

