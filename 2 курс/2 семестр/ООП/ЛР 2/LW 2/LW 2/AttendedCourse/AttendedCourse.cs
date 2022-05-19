using System;
using System.Collections.Generic;

namespace LW_2.AttendedCourse
{
    public abstract class AttendedCourse
    {
        public enum Status
        {
            Study,
            Certification,
            Expelled,
            Archive
        }

        public AttendedCourse(DateTimeOffset enrollmentDate, Student student, Course course)
        {
            EnrollmentDate = enrollmentDate;
            Student = student;
            Course = course;
            Results = new List<CourseWorkResult>();
            State = Status.Study;
            ExpellingDate = null;
            ArchiveDate = null;
            IsCertificated = false;
        }

        public bool TryToCreateResult(DateTimeOffset dateTime, bool isPassed, ushort score, CourseWorkRequirements work)
        {
            if (State != Status.Study)
                return false;

            CreateResult(dateTime, isPassed, score, work);

            return true;
        }
        protected abstract void CreateResult(DateTimeOffset dateTime, bool isPassed, ushort score, CourseWorkRequirements work);
        public abstract bool IsPassed();
        public bool TryToExpell(DateTimeOffset time)
        {
            if (State != Status.Study)
                return false;

            foreach (var result in Results)
                if (result.IsPassed)
                    return false;

            foreach (var work in Course.CourseWorks)
                if (work.Deadline < time)
                {
                    State = Status.Expelled;
                    ExpellingDate = time;
                    return true;
                }

            return false;
        }
        public bool TryToStartCertification()
        {
            if (!IsPassed() || State != Status.Study)
                return false;

            State = Status.Certification;
            return true;
        }
        public bool TryToChangeResultPassing(int index, bool isPassed)
        {
            if (State != Status.Certification)
                return false;

            Results[index].IsPassed = isPassed;

            return true;
        }
        public bool TryToChangeResultScore(int index, ushort score)
        {
            if (State != Status.Certification)
                return false;

            Results[index].Score = score;

            return true;
        }
        public bool TryToArchive(DateTimeOffset time, bool isCertificated)
        {
            if (State != Status.Certification)
                return false;

            ArchiveDate = time;
            IsCertificated = isCertificated;
            State = Status.Archive;

            return true;
        }

        public DateTimeOffset EnrollmentDate { get; }
        public string RegNumber { get { return Student.RegNumber; } }
        public Student Student { get; }
        public Course Course { get; }
        public List<CourseWorkResult> Results { get; }
        public Status State { get; private set; }
        public DateTimeOffset? ExpellingDate { get; private set; }
        public DateTimeOffset? ArchiveDate { get; private set; }
        public bool IsCertificated { get; private set; }
    }
}
