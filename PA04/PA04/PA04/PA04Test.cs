using System;
using System.Diagnostics;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.IO;

namespace PA04
{
	[TestClass]
	public class PA04Test
	{
		private const string EchoLite = "echo-lite.exe";
		private const string CatLite = "cat-lite.exe";

		[TestInitialize]
		public void SetUp()
		{
			Directory.SetCurrentDirectory(@"C:\Users\jordh_000\Documents\Purdue\ECE264\Solutions\PA04\PA04\Debug");
		}

		[TestMethod]
		public void TestCatLite()
		{
			//Process pProcess = new Process();
			//pProcess.StartInfo.FileName = EchoLite;
			//pProcess.StartInfo.Arguments = "Balls";
			//pProcess.StartInfo.UseShellExecute = false;
			//pProcess.StartInfo.RedirectStandardOutput = true;
			//pProcess.Start();
			//Assert.AreEqual("Balls ", pProcess.StandardOutput.ReadToEnd(), "Ya done goofed son.");
			//pProcess.WaitForExit();
		}

		[TestMethod]
		public void TestEchoLite()
		{
			//Process pProcess = new Process();
			//pProcess.StartInfo.FileName = EchoLite;
			//pProcess.StartInfo.Arguments = "Say cheese";
			//pProcess.StartInfo.UseShellExecute = false;
			//pProcess.StartInfo.RedirectStandardOutput = true;
			//pProcess.Start();
			//Assert.AreEqual("Say cheese ", pProcess.StandardOutput.ReadToEnd(), "Ya done goofed son.");
			//pProcess.WaitForExit();

			Process pProcess = new Process();
			pProcess.StartInfo.FileName = EchoLite;
			pProcess.StartInfo.Arguments = "\n";
			pProcess.StartInfo.UseShellExecute = false;
			pProcess.StartInfo.RedirectStandardOutput = true;
			pProcess.Start();
			Assert.AreEqual("\n", pProcess.StandardOutput.ReadToEnd(), "Ya done goofed son.");
			pProcess.WaitForExit();

			pProcess = new Process();
			pProcess.StartInfo.FileName = EchoLite;
			pProcess.StartInfo.Arguments = "note that    multiple space becomes 1.";
			pProcess.StartInfo.UseShellExecute = false;
			pProcess.StartInfo.RedirectStandardOutput = true;
			pProcess.Start();
			Assert.AreEqual("note that multiple space becomes 1.",
				pProcess.StandardOutput.ReadToEnd(), "Ya done goofed son.");
			pProcess.WaitForExit();

			pProcess = new Process();
			pProcess.StartInfo.FileName = EchoLite;
			pProcess.StartInfo.Arguments = "but you can"
			+ " use \" quotes \" to pass along spaces.";
			pProcess.StartInfo.UseShellExecute = false;
			pProcess.StartInfo.RedirectStandardOutput = true;
			pProcess.Start();
			Assert.AreEqual("but you can use  quotes  to pass along spaces.",
				pProcess.StandardOutput.ReadToEnd(), "Ya done goofed son.");
			pProcess.WaitForExit();
		}
	}
}
