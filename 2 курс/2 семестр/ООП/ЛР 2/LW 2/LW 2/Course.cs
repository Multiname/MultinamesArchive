using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace LW_2
{
    public class Course
    {
        public Course(uint code, string title, string professor, ushort passingScore, Rule ruleType)
        {
            if (!Regex.IsMatch(title.ToLower(), @"[a-z]+"))
                throw new ArgumentException("Title without letters");
            if (!Regex.IsMatch(professor.ToLower(), @"[a-z]+"))
                throw new ArgumentException("Professor's name without letters");

            Code = code;
            Title = title;
            Professor = professor;
            PassingScore = passingScore;
            CourseWorks = new List<CourseWorkRequirements>();
            RuleType = ruleType;
        }

        public enum Rule
        {
            OfSeventyFive,
            OfFifty,
            OfOneTime,
            OfThreeTimes,
            OfUnlimitedTimes,
            OfVariousTimes
        }

        public AttendedCourse.AttendedCourse EnrollStudent(
            DateTimeOffset enrollmentDate, Student student)
        {
            return RuleType switch
            {
                Rule.OfSeventyFive => new AttendedCourse.AttendedCourseWithRuleOfSeventyFive(enrollmentDate, student, this),
                Rule.OfFifty => new AttendedCourse.AttendedCourseWithRuleOfFifty(enrollmentDate, student, this),
                Rule.OfOneTime => new AttendedCourse.AttendedCourseWithRuleOfOneTime(enrollmentDate, student, this),
                Rule.OfThreeTimes => new AttendedCourse.AttendedCourseWithRuleOfThreeTimes(enrollmentDate, student, this),
                Rule.OfUnlimitedTimes => new AttendedCourse.AttendedCourseWithRuleOfUnlimitedTimes(enrollmentDate, student, this),
                Rule.OfVariousTimes => new AttendedCourse.AttendedCourseWithRuleOfVariousTimes(enrollmentDate, student, this),
                _ => throw new NotImplementedException()
            };
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
        public Rule RuleType { get; }
    }
}
