namespace ScrumPinboard.Models.Parameters
{
    public class LoginData
    {
        public string Login { get; set; }
        public string Password { get; set; }

        public LoginData(string login, string password)
        {
            Login = login;
            Password = password;
        }
    }
}
