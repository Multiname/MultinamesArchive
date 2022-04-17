namespace LW_2
{
    public class Student
    {
        public Student(uint regNumber, string fullName)
        {
            RegNumber = regNumber;
            FullName = fullName;
        }

        public uint RegNumber { get; }
        public string FullName { get; }
    }
}
