namespace ScrumPinboard.Models.Parameters
{
    public class SignupData
    {
        public string Name { get; set; }
        public string Login { get; set; }
        public string Password { get; set; }


        public SignupData(string name, string login, string password)
        {
            Name = name;
            Login = login;
            Password = password;
        }
    }
}
