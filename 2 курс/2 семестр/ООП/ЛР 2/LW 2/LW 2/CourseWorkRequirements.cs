using System;

namespace LW_2
{
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
}
