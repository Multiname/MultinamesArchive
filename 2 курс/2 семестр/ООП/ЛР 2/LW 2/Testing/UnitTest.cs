using Microsoft.VisualStudio.TestTools.UnitTesting;
using LW_2;
using System;

namespace Testing
{
    [TestClass]
    public class Testing
    {
        [TestMethod]
        public void TestRuleOfSeventyFive()
        {
            Student student = new Student(1, "Ivan");
            Course course = new Course(123, "Math", "Ramazanov A.K.", 70, Course.Rule.OfSeventyFive);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "DZ", 100, DateTimeOffset.Parse("10/03/2022"));
            LW_2.AttendedCourse.AttendedCourse attendedCourse = course.EnrollStudent(DateTimeOffset.Parse("01/03/2022"), student);

            attendedCourse.CreateResult(DateTimeOffset.Parse("05/03/2022"), false, 50, course.CourseWorks[0]);
            Assert.AreEqual(50, attendedCourse.Results[0].Score);

            attendedCourse.CreateResult(DateTimeOffset.Parse("15/03/2022"), true, 100, course.CourseWorks[0]);
            Assert.AreEqual(75, attendedCourse.Results[1].Score);

            attendedCourse.CreateResult(DateTimeOffset.Parse("17/03/2022"), true, 100, course.CourseWorks[0]);
            Assert.AreEqual(2, attendedCourse.Results.Count);
        }

        [TestMethod]
        public void TestRuleOfFifty()
        {
            Student student = new Student(1, "Ivan");
            Course course = new Course(123, "Math", "Ramazanov A.K.", 70, Course.Rule.OfFifty);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "DZ", 100, DateTimeOffset.Parse("10/03/2022"));
            LW_2.AttendedCourse.AttendedCourse attendedCourse = course.EnrollStudent(DateTimeOffset.Parse("01/03/2022"), student);

            attendedCourse.CreateResult(DateTimeOffset.Parse("05/03/2022"), false, 50, course.CourseWorks[0]);
            Assert.AreEqual(50, attendedCourse.Results[0].Score);

            attendedCourse.CreateResult(DateTimeOffset.Parse("15/03/2022"), true, 99, course.CourseWorks[0]);
            Assert.AreEqual(49, attendedCourse.Results[1].Score);

            attendedCourse.CreateResult(DateTimeOffset.Parse("17/03/2022"), true, 100, course.CourseWorks[0]);
            Assert.AreEqual(2, attendedCourse.Results.Count);
        }

        [TestMethod]
        public void TestRuleOfOneTime()
        {
            Student student = new Student(1, "Ivan");
            Course course = new Course(123, "Math", "Ramazanov A.K.", 70, Course.Rule.OfOneTime);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "DZ", 100, DateTimeOffset.Parse("10/03/2022"));
            course.CreateWork(CourseWorkRequirements.WorkType.Exam, "Exam", 100, DateTimeOffset.Parse("20/03/2022"));
            LW_2.AttendedCourse.AttendedCourse attendedCourse = course.EnrollStudent(DateTimeOffset.Parse("01/03/2022"), student);

            attendedCourse.CreateResult(DateTimeOffset.Parse("5/03/2022"), true, 80, course.CourseWorks[0]);
            attendedCourse.CreateResult(DateTimeOffset.Parse("12/03/2022"), true, 40, course.CourseWorks[0]);
            Assert.AreEqual(false, attendedCourse.IsPassed());

            attendedCourse.CreateResult(DateTimeOffset.Parse("14/03/2022"), true, 60, course.CourseWorks[0]);
            attendedCourse.CreateResult(DateTimeOffset.Parse("25/03/2022"), true, 60, course.CourseWorks[1]);
            Assert.AreEqual(2, attendedCourse.Results.Count);

            attendedCourse.CreateResult(DateTimeOffset.Parse("15/03/2022"), true, 60, course.CourseWorks[1]);
            attendedCourse.CreateResult(DateTimeOffset.Parse("17/03/2022"), true, 60, course.CourseWorks[1]);
            Assert.AreEqual(3, attendedCourse.Results.Count);
        }

        [TestMethod]
        public void TestRuleOfThreeTimes()
        {
            Student student = new Student(1, "Ivan");
            Course course = new Course(123, "Math", "Ramazanov A.K.", 70, Course.Rule.OfThreeTimes);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "DZ", 100, DateTimeOffset.Parse("10/03/2022"));
            LW_2.AttendedCourse.AttendedCourse attendedCourse = course.EnrollStudent(DateTimeOffset.Parse("01/03/2022"), student);

            attendedCourse.CreateResult(DateTimeOffset.Parse("5/03/2022"), true, 80, course.CourseWorks[0]);
            attendedCourse.CreateResult(DateTimeOffset.Parse("15/03/2022"), true, 40, course.CourseWorks[0]);
            Assert.AreEqual(true, attendedCourse.IsPassed());
            Assert.AreEqual(80, attendedCourse.Results[0].Score);
            Assert.AreEqual(40, attendedCourse.Results[1].Score);

            attendedCourse.CreateResult(DateTimeOffset.Parse("17/03/2022"), true, 50, course.CourseWorks[0]);
            Assert.AreEqual(50, attendedCourse.Results[2].Score);

            attendedCourse.CreateResult(DateTimeOffset.Parse("18/03/2022"), true, 100, course.CourseWorks[0]);
            Assert.AreEqual(80, attendedCourse.Results[3].Score);

            attendedCourse.CreateResult(DateTimeOffset.Parse("20/03/2022"), true, 100, course.CourseWorks[0]);
            Assert.AreEqual(4, attendedCourse.Results.Count);
        }

        [TestMethod]
        public void TestRuleOfUnlimitedTimes()
        {
            Student student = new Student(1, "Ivan");
            Course course = new Course(123, "Math", "Ramazanov A.K.", 70, Course.Rule.OfUnlimitedTimes);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "DZ", 100, DateTimeOffset.Parse("10/03/2022"));
            LW_2.AttendedCourse.AttendedCourse attendedCourse = course.EnrollStudent(DateTimeOffset.Parse("01/03/2022"), student);

            attendedCourse.CreateResult(DateTimeOffset.Parse("5/03/2022"), true, 80, course.CourseWorks[0]);
            attendedCourse.CreateResult(DateTimeOffset.Parse("7/03/2022"), true, 40, course.CourseWorks[0]);
            Assert.AreEqual(false, attendedCourse.IsPassed());
            Assert.AreEqual(40, attendedCourse.Results[1].Score);

            attendedCourse.CreateResult(DateTimeOffset.Parse("15/03/2022"), true, 100, course.CourseWorks[0]);
            Assert.AreEqual(85, attendedCourse.Results[2].Score);

            attendedCourse.CreateResult(DateTimeOffset.Parse("17/03/2022"), true, 100, course.CourseWorks[0]);
            Assert.AreEqual(4, attendedCourse.Results.Count);

            attendedCourse.CreateResult(DateTimeOffset.Parse("13/04/2022"), true, 100, course.CourseWorks[0]);
            Assert.AreEqual(4, attendedCourse.Results.Count);
        }

        [TestMethod]
        public void TestRuleOfVariousTimes()
        {
            Student student = new Student(1, "Ivan");
            Course course_1 = new Course(111, "Math", "Ramazanov A.K.", 85, Course.Rule.OfVariousTimes);
            course_1.CreateWork(CourseWorkRequirements.WorkType.Exam, "Exam", 100, DateTimeOffset.Parse("10/03/2022"));
            LW_2.AttendedCourse.AttendedCourse attendedCourse_1 = course_1.EnrollStudent(DateTimeOffset.Parse("01/03/2022"), student);

            attendedCourse_1.CreateResult(DateTimeOffset.Parse("5/03/2022"), true, 90, course_1.CourseWorks[0]);
            Assert.AreEqual(true, attendedCourse_1.IsPassed());
            attendedCourse_1.CreateResult(DateTimeOffset.Parse("6/03/2022"), true, 87, course_1.CourseWorks[0]);
            Assert.AreEqual(false, attendedCourse_1.IsPassed());
            attendedCourse_1.CreateResult(DateTimeOffset.Parse("7/03/2022"), true, 100, course_1.CourseWorks[0]);
            Assert.AreEqual(true, attendedCourse_1.IsPassed());

            attendedCourse_1.CreateResult(DateTimeOffset.Parse("8/03/2022"), true, 100, course_1.CourseWorks[0]);
            attendedCourse_1.CreateResult(DateTimeOffset.Parse("9/03/2022"), true, 100, course_1.CourseWorks[0]);
            Assert.AreEqual(4, attendedCourse_1.Results.Count);


            Course course_2 = new Course(222, "English", "Vlasko N.K.", 85, Course.Rule.OfVariousTimes);
            course_2.CreateWork(CourseWorkRequirements.WorkType.Exam, "Exam", 100, DateTimeOffset.Parse("10/03/2022"));
            LW_2.AttendedCourse.AttendedCourse attendedCourse_2 = course_2.EnrollStudent(DateTimeOffset.Parse("01/03/2022"), student);

            attendedCourse_2.CreateResult(DateTimeOffset.Parse("15/03/2022"), true, 100, course_2.CourseWorks[0]);
            Assert.AreEqual(false, attendedCourse_2.IsPassed());


            Course course_3 = new Course(333, "LITA", "Nikitenko U.V.", 85, Course.Rule.OfVariousTimes);
            course_3.CreateWork(CourseWorkRequirements.WorkType.Homework, "DZ", 100, DateTimeOffset.Parse("10/03/2022"));
            LW_2.AttendedCourse.AttendedCourse attendedCourse_3 = course_3.EnrollStudent(DateTimeOffset.Parse("01/03/2022"), student);

            attendedCourse_3.CreateResult(DateTimeOffset.Parse("15/03/2022"), true, 100, course_3.CourseWorks[0]);
            Assert.AreEqual(false, attendedCourse_3.IsPassed());

            attendedCourse_3.CreateResult(DateTimeOffset.Parse("21/03/2022"), true, 100, course_3.CourseWorks[0]);
            attendedCourse_3.CreateResult(DateTimeOffset.Parse("22/03/2022"), true, 100, course_3.CourseWorks[0]);
            attendedCourse_3.CreateResult(DateTimeOffset.Parse("23/03/2022"), true, 100, course_3.CourseWorks[0]);
            attendedCourse_3.CreateResult(DateTimeOffset.Parse("24/03/2022"), true, 100, course_3.CourseWorks[0]);
            attendedCourse_3.CreateResult(DateTimeOffset.Parse("25/03/2022"), true, 100, course_3.CourseWorks[0]);
            attendedCourse_3.CreateResult(DateTimeOffset.Parse("26/03/2022"), true, 100, course_3.CourseWorks[0]);
            Assert.AreEqual(6, attendedCourse_3.Results.Count);


            Course course_4 = new Course(444, "TISD", "Pchelinceva N.I.", 85, Course.Rule.OfVariousTimes);
            course_4.CreateWork(CourseWorkRequirements.WorkType.Test, "Test", 100, DateTimeOffset.Parse("10/03/2022"));
            LW_2.AttendedCourse.AttendedCourse attendedCourse_4 = course_4.EnrollStudent(DateTimeOffset.Parse("01/03/2022"), student);

            attendedCourse_4.CreateResult(DateTimeOffset.Parse("15/03/2022"), true, 100, course_4.CourseWorks[0]);
            Assert.AreEqual(false, attendedCourse_4.IsPassed());

            attendedCourse_4.CreateResult(DateTimeOffset.Parse("21/03/2022"), true, 100, course_4.CourseWorks[0]);
            attendedCourse_4.CreateResult(DateTimeOffset.Parse("22/03/2022"), true, 100, course_4.CourseWorks[0]);
            attendedCourse_4.CreateResult(DateTimeOffset.Parse("23/03/2022"), true, 100, course_4.CourseWorks[0]);
            attendedCourse_4.CreateResult(DateTimeOffset.Parse("24/03/2022"), true, 100, course_4.CourseWorks[0]);
            Assert.AreEqual(4, attendedCourse_4.Results.Count);
        }
    }
}
