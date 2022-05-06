using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

namespace LW_2.Loaders
{
    public class StudentDatLoader : IStudentFileLoader
    {
        public string Path { get; }

        public StudentDatLoader(string path) { Path = path; }

        public List<Student> Load()
        {
            if (!File.Exists(Path))
                throw new FileNotFoundException();

            List<Student> students = new List<Student>();

            foreach (string line in File.ReadAllLines(Path))
            {
                string[] data = line.Split('|');

                if (data.Length != 5)
                    throw new FileLoadException("Not enough fields");

                if (!Regex.IsMatch(data[0], @"^[A-Z]{2}-\d{5}/\d{2}\.\d{2}$"))
                    throw new FormatException("Incorrect registration number");

                if (!Regex.IsMatch(data[1], @"^[A-Z][a-z]+$"))
                    throw new FormatException("Incorrect first name");

                if (!Regex.IsMatch(data[2], @"^[A-Z][a-z]*$"))
                    throw new FormatException("Incorrect middle name");

                if (!Regex.IsMatch(data[3], @"^[A-Z][a-z]+$"))
                    throw new FormatException("Incorrect last name");

                if (!Regex.IsMatch(data[4], @"^\d{4}[-]\d{2}[-]\d{2}$"))
                    throw new FormatException("Incorrect birth date");

                students.Add(new Student(data[0].Split('.')[0], data[1] + " " + data[2] + " " + data[3], DateTimeOffset.Parse(data[4])));
            }

            return students;
        }
    }
}
