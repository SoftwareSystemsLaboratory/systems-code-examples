using System;
using System.IO;
using System.IO.Compression;
using System.Collections.Generic;
using System.Threading;

namespace threads
{
	//begin-class-PipelineComputation
	public class PipelineComputation {
		private readonly Queue<byte[]> _readData;
		private readonly Queue<byte[]> _compressionData;
		private volatile bool _reading = true;
		private volatile bool _compressing = true;

		public PipelineComputation () {
			_readData = new Queue<byte[]>();
			_compressionData = new Queue<byte[]>();
		}

		public void PerformCompression() {
			var readerThread = new Thread (FileReader);
			var compressThread = new Thread (Compression);
			var writerThread = new Thread (FileWriter);
			readerThread.Start ();
			compressThread.Start ();
			writerThread.Start ();
			readerThread.Join ();
			compressThread.Join ();
			writerThread.Join ();
		}

		private void FileReader() {
			using (var stream = new FileStream("file.txt", FileMode.Open, FileAccess.Read)) {
				int len;
				var buffer = new byte[1024];
				while ((len = stream.Read(buffer, 0, buffer.Length)) > 0) {
					if (len != buffer.Length) {
						Array.Resize (ref buffer, len);
					}
					lock (_readData) {
						while (_readData.Count > 10) {
							Monitor.Wait (_readData);
						}
						_readData.Enqueue(buffer);
						Monitor.Pulse (_readData);
					}
				}
			}
			_reading = false;
		}

		private void Compression() {
			var workLeft = false;
			while (_reading || workLeft) {
				workLeft = false;
				byte[] dataToCompress = null;
				lock (_readData) {
					while (_reading && _readData.Count == 0) {
						Monitor.Wait (_readData, 100);
					}
					workLeft = _readData.Count > 1;
					if (_readData.Count > 0) {
						dataToCompress = _readData.Dequeue ();
					}
				}
				if (dataToCompress != null) {
					var compressed = Compress(dataToCompress);
					lock (_compressionData) {
						while (_compressionData.Count > 10) {
							Monitor.Wait (_compressionData, 100);
						}
						_compressionData.Enqueue (compressed);
						Monitor.Pulse (_compressionData);
					}
				}
			}
			_compressing = false;
		}

		private static byte[] Compress(byte[] data) {
			var memStream = new MemoryStream ();
			using(var compressionStream = new GZipStream(memStream, CompressionMode.Compress)) {
				compressionStream.Write(data, 0, data.Length);
			}
			return memStream.ToArray ();
		}

		private void FileWriter() {
			using (var stream = new FileStream("file.gz", FileMode.OpenOrCreate, FileAccess.Write)) {
				var workLeft = false;
				while (_compressing || workLeft) {
					workLeft = false;
					byte[] compressedData = null;
					lock (_compressionData) {
						while (_compressionData.Count == 0 && _compressing) {
							Monitor.Wait (_compressionData, 100);
						}
						workLeft = _compressionData.Count > 1;
						if (_compressionData.Count > 0) {
							compressedData = _compressionData.Dequeue ();
						}
					}
					if (compressedData != null) {
						stream.Write (compressedData, 0, compressedData.Length);
					}
				}
			}
		}
	}
	//end-class-PipelineComputation
}

