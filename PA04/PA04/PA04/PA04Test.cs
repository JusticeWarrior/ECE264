using System;
using System.Diagnostics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PA04
{
	[TestClass]
	public class PA04Test
	{
		private string CatLite = "cat-lite.exe";
		
		[TestMethod]
		public void TestCatLite()
		{
			Process pProcess = new Process();
			pProcess.StartInfo.FileName = CatLite;
		}
	}
}
