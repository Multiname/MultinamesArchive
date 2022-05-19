using Microsoft.VisualStudio.TestTools.UnitTesting;
using LW_2.AttendedCourse;
using LW_2;
using System;

namespace Testing
{
    [TestClass]
    public class Testing
    {
        [TestMethod]
        public void TestExpelledState()
        {
            Student mike = new Student("2", "Mike", DateTimeOffset.Parse("02.02.2002"));
            Course course = new Course(1, "Math", "Ivanov I.I.", 80, Course.Rule.OfFifty);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "Homework", 70, DateTimeOffset.Parse("25.05.2022"));
            course.CreateWork(CourseWorkRequirements.WorkType.Exam, "Exam", 30, DateTimeOffset.Parse("30.05.2022"));
            AttendedCourse mikeCourse = course.EnrollStudent(DateTimeOffset.Parse("19.05.2022"), mike);

            mikeCourse.TryToExpell(DateTimeOffset.Parse("27.05.2022"));

            Assert.AreEqual(false, mikeCourse.TryToCreateResult(DateTimeOffset.Parse("27.05.2022"), true, 50, mikeCourse.Course.CourseWorks[0]));
            Assert.AreEqual(false, mikeCourse.TryToExpell(DateTimeOffset.Parse("29.05.2022")));
            Assert.AreEqual(false, mikeCourse.TryToStartCertification());
            Assert.AreEqual(false, mikeCourse.TryToChangeResultPassing(0, false));
            Assert.AreEqual(false, mikeCourse.TryToChangeResultScore(0, 25));
            Assert.AreEqual(false, mikeCourse.TryToArchive(DateTimeOffset.Parse("01.06.2022"), false));
        }

        [TestMethod]
        public void TestStudyState()
        {
            Student bob = new Student("1", "Bob", DateTimeOffset.Parse("01.01.2001"));
            Student mike = new Student("2", "Mike", DateTimeOffset.Parse("02.02.2002"));
            Course course = new Course(1, "Math", "Ivanov I.I.", 80, Course.Rule.OfFifty);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "Homework", 70, DateTimeOffset.Parse("25.05.2022"));
            course.CreateWork(CourseWorkRequirements.WorkType.Exam, "Exam", 30, DateTimeOffset.Parse("30.05.2022"));
            AttendedCourse bobCourse = course.EnrollStudent(DateTimeOffset.Parse("19.05.2022"), bob);
            AttendedCourse mikeCourse = course.EnrollStudent(DateTimeOffset.Parse("19.05.2022"), mike);

            Assert.AreEqual(true, bobCourse.TryToCreateResult(DateTimeOffset.Parse("23.05.2022"), true, 70, bobCourse.Course.CourseWorks[0]));
            Assert.AreEqual(false, bobCourse.TryToChangeResultScore(0, 30));
            Assert.AreEqual(false, bobCourse.TryToChangeResultPassing(0, false));
            Assert.AreEqual(false, bobCourse.TryToArchive(DateTimeOffset.Parse("01.06.2022"), true));

            Assert.AreEqual(false, bobCourse.TryToExpell(DateTimeOffset.Parse("27.05.2022")));
            Assert.AreEqual(true, mikeCourse.TryToExpell(DateTimeOffset.Parse("27.05.2022")));
            Assert.AreEqual(AttendedCourse.Status.Expelled, mikeCourse.State);

            Assert.AreEqual(false, bobCourse.TryToStartCertification());
            bobCourse.TryToCreateResult(DateTimeOffset.Parse("30.05.2022"), true, 25, bobCourse.Course.CourseWorks[1]);
            Assert.AreEqual(true, bobCourse.TryToStartCertification());
        }

        [TestMethod]
        public void TestCertificationState()
        {
            Student bob = new Student("1", "Bob", DateTimeOffset.Parse("01.01.2001"));
            Course course = new Course(1, "Math", "Ivanov I.I.", 80, Course.Rule.OfFifty);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "Homework", 70, DateTimeOffset.Parse("25.05.2022"));
            course.CreateWork(CourseWorkRequirements.WorkType.Exam, "Exam", 30, DateTimeOffset.Parse("30.05.2022"));
            AttendedCourse bobCourse = course.EnrollStudent(DateTimeOffset.Parse("19.05.2022"), bob);

            bobCourse.TryToCreateResult(DateTimeOffset.Parse("23.05.2022"), true, 70, bobCourse.Course.CourseWorks[0]);
            bobCourse.TryToCreateResult(DateTimeOffset.Parse("30.05.2022"), true, 25, bobCourse.Course.CourseWorks[1]);
            bobCourse.TryToStartCertification();

            Assert.AreEqual(false, bobCourse.TryToCreateResult(DateTimeOffset.Parse("01.06.2022"), true, 30, bobCourse.Course.CourseWorks[1]));
            Assert.AreEqual(false, bobCourse.TryToExpell(DateTimeOffset.Parse("01.06.2022")));
            Assert.AreEqual(false, bobCourse.TryToStartCertification());

            Assert.AreEqual(true, bobCourse.TryToChangeResultScore(0, 30));
            Assert.AreEqual(true, bobCourse.TryToChangeResultPassing(0, false));
            Assert.AreEqual(true, bobCourse.TryToArchive(DateTimeOffset.Parse("01.06.2022"), true));
            Assert.AreEqual(AttendedCourse.Status.Archive, bobCourse.State);
            Assert.AreEqual(true, bobCourse.IsCertificated);
        }

        [TestMethod]
        public void TestArchiveState()
        {
            Student bob = new Student("1", "Bob", DateTimeOffset.Parse("01.01.2001"));
            Course course = new Course(1, "Math", "Ivanov I.I.", 80, Course.Rule.OfFifty);
            course.CreateWork(CourseWorkRequirements.WorkType.Homework, "Homework", 70, DateTimeOffset.Parse("25.05.2022"));
            course.CreateWork(CourseWorkRequirements.WorkType.Exam, "Exam", 30, DateTimeOffset.Parse("30.05.2022"));
            AttendedCourse bobCourse = course.EnrollStudent(DateTimeOffset.Parse("19.05.2022"), bob);

            bobCourse.TryToCreateResult(DateTimeOffset.Parse("23.05.2022"), true, 70, bobCourse.Course.CourseWorks[0]);
            bobCourse.TryToCreateResult(DateTimeOffset.Parse("30.05.2022"), true, 25, bobCourse.Course.CourseWorks[1]);
            bobCourse.TryToStartCertification();
            bobCourse.TryToArchive(DateTimeOffset.Parse("01.06.2022"), true);

            Assert.AreEqual(false, bobCourse.TryToCreateResult(DateTimeOffset.Parse("01.06.2022"), true, 30, bobCourse.Course.CourseWorks[1]));
            Assert.AreEqual(false, bobCourse.TryToExpell(DateTimeOffset.Parse("01.06.2022")));
            Assert.AreEqual(false, bobCourse.TryToStartCertification());
            Assert.AreEqual(false, bobCourse.TryToChangeResultScore(0, 30));
            Assert.AreEqual(false, bobCourse.TryToChangeResultPassing(0, false));
            Assert.AreEqual(false, bobCourse.TryToArchive(DateTimeOffset.Parse("02.06.2022"), false));
        }
    }
}
