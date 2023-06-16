using Microsoft.IdentityModel.Tokens;
using System.Text;

namespace ScrumPinboard
{
    public static class AuthOptions
    {
        public const string ISSUER = "ScrumPinboardServer";
        public const string AUDIENCE = "ScrumPinboardClient";
        public const string KEY = "PleaseDontHackMe";
        public static SymmetricSecurityKey GetSymmetricSecurityKey() =>
            new SymmetricSecurityKey(Encoding.UTF8.GetBytes(KEY));
    }
}
