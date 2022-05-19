using System;
using System.Text.RegularExpressions;

namespace LW_2
{
    public class CourseWorkRequirements
    {
        public CourseWorkRequirements(WorkType type, string title, ushort maxScore, DateTimeOffset deadline)
        {
            if (!Regex.IsMatch(title.ToLower(), @"[a-z]+"))
                throw new ArgumentException("Title without letters");
            if (maxScore == 0)
                throw new ArgumentException("Max score can't be equal to 0");

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
}
