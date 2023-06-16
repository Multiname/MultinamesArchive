using System.ComponentModel.DataAnnotations.Schema;
using System.Text.Json.Serialization;

namespace ScrumPinboard.Models
{
    [Table("developers")]
    public class Developer
    {
        [JsonIgnore]
        [Column("id")]
        public int Id { get; set; }

        [Column("login")]
        public string Login { get; set; } = "";

        [Column("password")]
        public string Password { get; set; } = "";

        [Column("name")]
        public string Name { get; set; } = "";

        [Column("tag")]
        public string Tag { get; set; } = "";



        [JsonIgnore]
        public List<Project> Projects { get; set; } = new List<Project>();

        [JsonIgnore]
        public List<DeveloperProject> DevelopersProjects { get; set; } = new List<DeveloperProject>();



        [JsonIgnore]
        public List<Story> Stories { get; set; } = new List<Story>();
    }
}
