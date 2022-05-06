using Microsoft.VisualStudio.TestTools.UnitTesting;
using LW_2.Loaders;
using System.Collections.Generic;
using LW_2;
using System;

namespace Testing
{
    [TestClass]
    public class Testing
    {
        [TestMethod]
        public void TestCsvLoad()
        {
            StudentCSVLoader loader = new StudentCSVLoader("D:\\Students.csv");

            List<Student> students = loader.Load();

            Assert.AreEqual(students[0].RegNumber, "CS-00345/14");
            Assert.AreEqual(students[1].FullName, "Andrew Peters");
            Assert.AreEqual(students[2].BirthDate, DateTimeOffset.Parse("05.11.1985"));
        }

        [TestMethod]
        public void TestDatLoad()
        {
            StudentDatLoader loader = new StudentDatLoader("D:\\Students.dat");

            List<Student> students = loader.Load();

            Assert.AreEqual(students[0].RegNumber, "CS-00345/14");
            Assert.AreEqual(students[1].FullName, "Andrew B Peters");
            Assert.AreEqual(students[2].BirthDate, DateTimeOffset.Parse("05.11.1985"));
        }
    }
}
