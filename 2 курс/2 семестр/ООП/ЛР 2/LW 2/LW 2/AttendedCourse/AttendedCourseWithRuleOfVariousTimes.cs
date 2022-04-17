using System;
using System.Collections.Generic;

namespace LW_2.AttendedCourse
{
    class AttendedCourseWithRuleOfVariousTimes : AttendedCourse
    {
        public AttendedCourseWithRuleOfVariousTimes(DateTimeOffset enrollmentDate,
            Student student, Course course) : base(enrollmentDate, student, course) { }

        public override void CreateResult(DateTimeOffset dateTime, bool isPassed, ushort score, CourseWorkRequirements work)
        {
            int number = 0;
            foreach (CourseWorkResult result in Results)
                if (result.Requirements == work)
                    ++number;

            if (work.Type == CourseWorkRequirements.WorkType.Homework)
            {
                if (number > 5)
                    return;
            }
            else if (number > 3)
                return;

            if (dateTime > work.Deadline)
                if (work.Type == CourseWorkRequirements.WorkType.Homework)
                    score = (ushort)Math.Ceiling(score * 0.8);
                else if (work.Type == CourseWorkRequirements.WorkType.Test)
                    score = (ushort)Math.Ceiling(score * 0.75);
                else
                    score = (ushort)Math.Ceiling(score * 0.6);
            Results.Add(new CourseWorkResult(dateTime, isPassed, score, work));
        }

        private struct ResultRetakePair
        {
            public ResultRetakePair(CourseWorkResult result, bool isRetaken)
            {
                this.result = result;
                this.isRetaken = isRetaken;
            }

            public CourseWorkResult result;
            public bool isRetaken;
        }

        public override bool IsPassed()
        {
            List<ResultRetakePair> finalResults = new List<ResultRetakePair>();
            foreach (CourseWorkResult result in Results)
            {
                bool isFound = false;
                for (int i = 0; i < finalResults.Count; ++i)
                    if (result.Requirements == finalResults[i].result.Requirements)
                    {
                        isFound = true;
                        ResultRetakePair pair = finalResults[i];
                        pair.isRetaken = true;
                        if (result.Score > finalResults[i].result.Score)
                            pair.result = result;
                        finalResults[i] = pair;
                    }
                if (!isFound)
                    finalResults.Add(new ResultRetakePair(result, false));
            }

            ushort sum = 0;
            foreach (ResultRetakePair pair in finalResults)
                if (pair.result.IsPassed)
                    if (pair.isRetaken)
                        sum += (ushort)(pair.result.Score * 0.9);
                    else
                        sum += pair.result.Score;

            return sum >= Course.PassingScore;
        }
    }
}
