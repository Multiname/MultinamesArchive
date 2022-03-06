using Microsoft.VisualStudio.TestTools.UnitTesting;
using LW_2;
using System;

namespace Testing
{
    [TestClass]
    public class Testing
    {
        [TestMethod]
        public void TestWorkCreating()
        {
            Course course = new Course(123, "Math", "Ramazanov A.K.", 70);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "DZ", 20, DateTimeOffset.Parse("06/03/2022"));
            Assert.AreEqual(1, course.CourseWorks.Count);
            Assert.AreEqual("DZ", course.CourseWorks[0].Title);
        }

        [TestMethod]
        public void TestResultCreating()
        {
            Student student = new Student(111, "Ivanov I.I.");
            Course course = new Course(123, "Math", "Ramazanov A.K.", 70);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "DZ", 20, DateTimeOffset.Parse("11/03/2022"));
            AttendedCourse attendedCourse = new AttendedCourse(DateTimeOffset.Parse("01/03/2022"), student, course);
            attendedCourse.CreateResult(DateTimeOffset.Parse("10/03/2022"), false, 5, course.CourseWorks[0]);
            attendedCourse.CreateResult(DateTimeOffset.Parse("12/03/2022"), true, 18, course.CourseWorks[0]);
            attendedCourse.CreateResult(DateTimeOffset.Parse("13/03/2022"), true, 20, course.CourseWorks[0]);
            Assert.AreEqual(2, attendedCourse.Results.Count);
            Assert.AreEqual(5, attendedCourse.Results[0].Score);
            Assert.AreEqual(13, attendedCourse.Results[1].Score);
        }

        [TestMethod]
        public void TestCoursePassing()
        {
            Student student = new Student(111, "Ivanov I.I.");
            Course course = new Course(123, "Math", "Ramazanov A.K.", 70);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "DZ", 70, DateTimeOffset.Parse("11/03/2022"));
            AttendedCourse attendedCourse = new AttendedCourse(DateTimeOffset.Parse("01/03/2022"), student, course);
            Assert.AreEqual(false, attendedCourse.IsPassed());
            attendedCourse.CreateResult(DateTimeOffset.Parse("10/03/2022"), true, 70, course.CourseWorks[0]);
            Assert.AreEqual(true, attendedCourse.IsPassed());
        }
    }
}
