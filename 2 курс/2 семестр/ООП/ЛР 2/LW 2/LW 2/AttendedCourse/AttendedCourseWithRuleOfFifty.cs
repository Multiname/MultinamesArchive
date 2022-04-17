﻿using System;

namespace LW_2.AttendedCourse
{
    public class AttendedCourseWithRuleOfFifty: AttendedCourse
    {
        public AttendedCourseWithRuleOfFifty(DateTimeOffset enrollmentDate,
            Student student, Course course) : base(enrollmentDate, student, course) { }

        public override void CreateResult(DateTimeOffset dateTime, bool isPassed, ushort score, CourseWorkRequirements work)
        {
            foreach (CourseWorkResult result in Results)
                if (result.Requirements == work)
                    if (result.IsPassed)
                        return;

            if (dateTime > work.Deadline)
                score = (ushort)(score * 0.5);

            Results.Add(new CourseWorkResult(dateTime, isPassed, score, work));
        }

        public override bool IsPassed()
        {
            ushort sum = 0;
            foreach (CourseWorkResult result in Results)
                if (result.IsPassed)
                    sum += result.Score;

            return sum >= Course.PassingScore;
        }
    }
}
