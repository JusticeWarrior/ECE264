using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Diagnostics;
using System.IO;

namespace PA05.Test
{
	[TestClass]
	public class PA05Tester
	{
		private const string TestFile = "PA05";

		[TestInitialize]
		public void SetUp()
		{
			Directory.SetCurrentDirectory(@"C:\Users\jordh_000\Documents\Purdue\ECE264\Solutions\PA05\PA05\Debug");
		}


		private const string PartitionAll = "partitionAll ";

		[TestMethod]
		public void TestPartitionAll()
		{
			Process pProcess = new Process();
			pProcess.StartInfo.FileName = TestFile;
			pProcess.StartInfo.Arguments = PartitionAll + "5";
			pProcess.StartInfo.UseShellExecute = false;
			pProcess.StartInfo.RedirectStandardOutput = true;
			pProcess.Start();
			Assert.AreEqual("Yo whatup!", pProcess.StandardOutput.ReadToEnd(), "Ya done goofed son.");
			pProcess.WaitForExit();
		}
	}
}
