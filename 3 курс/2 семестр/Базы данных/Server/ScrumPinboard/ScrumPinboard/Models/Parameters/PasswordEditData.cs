namespace ScrumPinboard.Models.Parameters
{
    public class PasswordEditData
    {
        public string OldPassword { get; set; }
        public string NewPassword { get; set; }

        public PasswordEditData(string oldPassword, string newPassword)
        {
            OldPassword = oldPassword;
            NewPassword = newPassword;
        }
    }
}
