using System;

namespace LW_2
{
    public class CourseWorkResult
    {
        public CourseWorkResult(DateTimeOffset dateTime, bool isPassed, ushort score, CourseWorkRequirements requirements)
        {
            DateTime = dateTime;
            IsPassed = isPassed;
            if (score > requirements.MaxScore)
                Score = requirements.MaxScore;
            else
                Score = score;
            Requirements = requirements;
        }

        public DateTimeOffset DateTime { get; }
        public bool IsPassed { get; set; }
        public ushort Score { get; set; }
        public CourseWorkRequirements Requirements { get; }
    }
}
