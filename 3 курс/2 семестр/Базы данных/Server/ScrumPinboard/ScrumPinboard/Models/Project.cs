using System.ComponentModel.DataAnnotations.Schema;
using System.Text.Json.Serialization;

namespace ScrumPinboard.Models
{
    [Table("projects")]
    public class Project
    {
        [JsonIgnore]
        [Column("id")]
        public int Id { get; set; }

        [Column("name")]
        public string Name { get; set; } = "";



        [JsonIgnore]
        public List<Developer> Developers { get; set; } = new List<Developer>();

        [JsonIgnore]
        public List<DeveloperProject> DevelopersProjects { get; set; } = new List<DeveloperProject>();



        [JsonIgnore]
        public List<Epic> Epics { get; set; } = new List<Epic>();

        [JsonIgnore]
        public List<Sprint> Sprints { get; set; } = new List<Sprint>();
    }
}
