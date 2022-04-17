using System;
using System.Collections.Generic;

namespace LW_2.AttendedCourse
{
    public abstract class AttendedCourse
    {
        public AttendedCourse(DateTimeOffset enrollmentDate, Student student, Course course)
        {
            EnrollmentDate = enrollmentDate;
            Student = student;
            Course = course;
            Results = new List<CourseWorkResult>();
        }

        public abstract void CreateResult(DateTimeOffset dateTime, bool isPassed, ushort score, CourseWorkRequirements work);
        public abstract bool IsPassed();

        public DateTimeOffset EnrollmentDate { get; }
        public uint RegNumber { get { return Student.RegNumber; } }
        public Student Student { get; }
        public Course Course { get; }
        public List<CourseWorkResult> Results { get; }
    }
}
