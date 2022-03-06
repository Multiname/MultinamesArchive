using System;
using System.Collections.Generic;

namespace LW_2
{
    public class Student
    {
        public Student(uint regNumber, string fullName)
        {
            RegNumber = regNumber;
            FullName = fullName;
        }

        public uint RegNumber { get; }
        public string FullName { get; }
    }

    public class AttendedCourse
    {
        public AttendedCourse(DateTimeOffset enrollmentDate, Student student, Course course)
        {
            EnrollmentDate = enrollmentDate;
            Student = student;
            Course = course;
            Results = new List<CourseWorkResult>();
        }

        public void CreateResult(DateTimeOffset dateTime, bool isPassed, ushort score, CourseWorkRequirements work)
        {
            foreach (CourseWorkResult result in Results)
            {
                if (result.Requirements == work)
                {
                    if (result.IsPassed)
                    {
                        return;
                    }
                }
            }

            Results.Add(new CourseWorkResult(dateTime, isPassed, score, work));
        }

        public bool IsPassed()
        {
            ushort sum = 0;
            foreach (CourseWorkResult result in Results)
            {
                if (result.IsPassed)
                {
                    sum += result.Score;
                }
            }

            return sum >= Course.PassingScore;
        }

        public DateTimeOffset EnrollmentDate { get; }
        public uint RegNumber { get { return Student.RegNumber; } }
        public Student Student { get; }
        public Course Course { get; }
        public List<CourseWorkResult> Results { get; }
    }

    public class Course
    {
        public Course(uint code, string title, string professor, ushort passingScore)
        {
            Code = code;
            Title = title;
            Professor = professor;
            PassingScore = passingScore;
            CourseWorks = new List<CourseWorkRequirements>();
        }

        public void CreateWork(CourseWorkRequirements.WorkType type, string title, ushort maxScore, DateTimeOffset deadline)
        {
            CourseWorks.Add(new CourseWorkRequirements(type, title, maxScore, deadline));
        }

        public uint Code { get; }
        public string Title { get; }
        public string Professor { get; }
        public ushort PassingScore { get; }
        public List<CourseWorkRequirements> CourseWorks { get; }
    }

    public class CourseWorkRequirements
    {
        public CourseWorkRequirements(WorkType type, string title, ushort maxScore, DateTimeOffset deadline)
        {
            Type = type;
            Title = title;
            MaxScore = maxScore;
            Deadline = deadline;
        }

        public enum WorkType
        {
            Test,
            Homework,
            Exam
        }

        public WorkType Type { get; }
        public string Title { get; }
        public ushort MaxScore { get; }
        public DateTimeOffset Deadline { get; }
    }

    public class CourseWorkResult
    {
        public CourseWorkResult(DateTimeOffset dateTime, bool isPassed, ushort score, CourseWorkRequirements requirements)
        {
            DateTime = dateTime;
            IsPassed = isPassed;
            if (dateTime > requirements.Deadline)
            {
                Score = (ushort)(score * 0.75);
            }
            else
            {
                Score = score;
            }
            if (Score > requirements.MaxScore)
            {
                Score = requirements.MaxScore;
            }
            Requirements = requirements;
        }

        public DateTimeOffset DateTime { get; }
        public bool IsPassed { get; }
        public ushort Score { get; }
        public CourseWorkRequirements Requirements { get; }
    }

    public class LW_2
    {
        public static void Main() { }
    }
}
