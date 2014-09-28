using System;
using System.Diagnostics;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.IO;

namespace PA04
{
	[TestClass]
	public class PA04Test
	{
		private const string CatLite = "cat-lite.exe";
		
		[TestMethod]
		public void TestCatLite()
		{
			Directory.SetCurrentDirectory(@"C:\Users\jordh_000\Documents\Purdue\ECE264\Solutions\PA04\PA04\Debug");
			Process pProcess = new Process();
			pProcess.StartInfo.FileName = CatLite;
			pProcess.StartInfo.Arguments = "Balls";
			pProcess.StartInfo.UseShellExecute = false;
			pProcess.StartInfo.RedirectStandardOutput = true;
			pProcess.Start();

			Assert.AreEqual("Balls", pProcess.StandardOutput.ReadToEnd(), "Ya done goofed son.");
			pProcess.WaitForExit();
		}
	}
}
