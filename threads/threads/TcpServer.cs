using System;
using System.Threading;
using System.Net.Sockets;
using System.Net;
using System.Text;

namespace DistributedSystemsSamples
{
	//begin-class-TcpServer
	public class TcpServer
	{
		private Socket _socket;
		private Thread _serverThread;

		public TcpServer() {
			_socket = new Socket (AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			_serverThread = new Thread (Server);
			_serverThread.Start ();
		}

		private void Server() {
			_socket.Bind (new IPEndPoint (IPAddress.Any, 8080));
			_socket.Listen (100);
			while (true) {
				var serverClientSocket = _socket.Accept ();
				new Thread (Server) { IsBackground = true }.Start (serverClientSocket);
			}
		}

		private void ServerThread(Object arg) {
			try {
				var socket = (Socket)arg;
				socket.Send (Encoding.UTF8.GetBytes ("Echo"));
			} catch(SocketException se) {
				Console.WriteLine (se.Message);
			}
		}
	}

	public class TcpClient {
		public void ConnectToServer() {
			var socket = new Socket (AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			socket.Connect (new IPEndPoint (IPAddress.Parse("127.0.0.1"), 8080));
			var buffer = new byte[1024];
			var receivedBytes = socket.Receive (buffer);
			if (receivedBytes > 0) {
				Array.Resize (ref buffer, receivedBytes);
				Console.WriteLine (System.Text.Encoding.UTF8.GetString (buffer));
			}
		}
	}
	//end-class-TcpServer
}

