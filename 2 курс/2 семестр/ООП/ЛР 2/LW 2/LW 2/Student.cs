using System;
using System.Text.RegularExpressions;

namespace LW_2
{
    public class Student
    {
        public Student() : this("", "", DateTimeOffset.Parse("01/01/01")) { }
        public Student(string regNumber, string fullName) : this(regNumber, fullName, DateTimeOffset.Parse("01/01/01")) { }
        public Student(string regNumber, string fullName, DateTimeOffset birthDate)
        {
            if (!Regex.IsMatch(fullName.ToLower(), @"[a-z]+"))
                throw new ArgumentException("Name without letters");

            RegNumber = regNumber;
            FullName = fullName;
            BirthDate = birthDate;
        }

        public string RegNumber { get; }
        public string FullName { get; }
        public DateTimeOffset BirthDate { get; }
    }
}
