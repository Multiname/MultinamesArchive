using System.ComponentModel.DataAnnotations.Schema;
using System.Text.Json.Serialization;

namespace ScrumPinboard.Models
{
    [Table("sprints")]
    public class Sprint
    {
        [JsonIgnore]
        [Column("id")]
        public int Id { get; set; }

        [Column("name")]
        public string Name { get; set; } = "";

        [Column("project_id")]
        public int ProjectId { get; set; }

        [Column("start_date")]
        public DateTime StartDate { get; set; }

        [Column("end_date")]
        public DateTime EndDate { get; set; }



        [JsonIgnore]
        public Project Project { get; set; } = new Project();



        [JsonIgnore]
        public List<Story> Stories { get; set; } = new List<Story>();

        [JsonIgnore]
        public List<SprintStory> SprintsStories { get; set; } = new List<SprintStory>();
    }
}
