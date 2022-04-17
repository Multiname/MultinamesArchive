using System;
using System.Collections.Generic;

namespace LW_2.AttendedCourse
{
    class AttendedCourseWithRuleOfOneTime : AttendedCourse
    {
        public AttendedCourseWithRuleOfOneTime(DateTimeOffset enrollmentDate,
            Student student, Course course) : base(enrollmentDate, student, course) { }

        public override void CreateResult(DateTimeOffset dateTime, bool isPassed, ushort score, CourseWorkRequirements work)
        {
            if (work.Type == CourseWorkRequirements.WorkType.Exam)
            {
                foreach (CourseWorkResult result in Results)
                    if (result.Requirements == work)
                            return;

                if (work.Deadline < dateTime)
                    return;
            }
            else
            {
                int number = 0;
                foreach (CourseWorkResult result in Results)
                    if (result.Requirements == work)
                        ++number;

                if (number > 1)
                    return;
            }

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
