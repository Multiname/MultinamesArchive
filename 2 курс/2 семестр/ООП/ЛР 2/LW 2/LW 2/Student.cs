using System;

namespace LW_2
{
    public class Student
    {
        public Student()
        {
            RegNumber = "";
            FullName = "";
            BirthDate = DateTimeOffset.Parse("01/01/01");
        }

        public Student(string regNumber, string fullName)
        {
            RegNumber = regNumber;
            FullName = fullName;
            BirthDate = DateTimeOffset.Parse("01/01/01");
        }

        public Student(string regNumber, string fullName, DateTimeOffset birthDate)
        {
            RegNumber = regNumber;
            FullName = fullName;
            BirthDate = birthDate;
        }

        public string RegNumber { get; }
        public string FullName { get; }
        public DateTimeOffset BirthDate { get; }
    }
}
