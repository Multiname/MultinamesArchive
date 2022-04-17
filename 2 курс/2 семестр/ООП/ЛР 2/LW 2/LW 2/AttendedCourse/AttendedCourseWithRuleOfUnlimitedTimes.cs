using System;
using System.Collections.Generic;

namespace LW_2.AttendedCourse
{
    class AttendedCourseWithRuleOfUnlimitedTimes : AttendedCourse
    {
        public AttendedCourseWithRuleOfUnlimitedTimes(DateTimeOffset enrollmentDate,
            Student student, Course course) : base(enrollmentDate, student, course) { }

        public override void CreateResult(DateTimeOffset dateTime, bool isPassed, ushort score, CourseWorkRequirements work)
        {
            double lateness = (dateTime - work.Deadline).TotalDays;
            if (lateness >= 0 && lateness <= 7)
                score = (ushort)(score * 0.85);
            else if (lateness > 7)
                return;

            Results.Add(new CourseWorkResult(dateTime, isPassed, score, work));
        }

        public override bool IsPassed()
        {
            List<CourseWorkResult> finalResults = new List<CourseWorkResult>();
            foreach (CourseWorkResult result in Results)
            {
                bool isFound = false;
                for (int i = 0; i < finalResults.Count; ++i)
                    if (result.Requirements == finalResults[i].Requirements)
                    {
                        isFound = true;
                        if (result.DateTime > finalResults[i].DateTime)
                            finalResults[i] = result;
                    }
                if (!isFound)
                    finalResults.Add(result);
            }

            ushort sum = 0;
            foreach (CourseWorkResult result in finalResults)
                if (result.IsPassed)
                    sum += result.Score;

            return sum >= Course.PassingScore;
        }
    }
}
