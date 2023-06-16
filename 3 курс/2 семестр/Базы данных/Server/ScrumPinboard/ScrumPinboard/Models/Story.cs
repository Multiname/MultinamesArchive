using System.ComponentModel.DataAnnotations.Schema;
using System.Text.Json.Serialization;

namespace ScrumPinboard.Models
{
    [Table("stories")]
    public class Story
    {
        [JsonIgnore]
        [Column("id")]
        public int Id { get; set; }

        [Column("name")]
        public string Name { get; set; } = "";

        [Column("epic_id")]
        public int EpicId { get; set; }

        [Column("developer_id")]
        public int? DeveloperId { get; set; }

        [Column("story_points")]
        public int StoryPoints { get; set; }



        [JsonIgnore]
        public Epic Epic { get; set; } = new Epic();

        [JsonIgnore]
        public Developer? Developer { get; set; }



        [JsonIgnore]
        public List<Sprint> Sprints { get; set; } = new List<Sprint>();

        [JsonIgnore]
        public List<SprintStory> SprintsStories { get; set; } = new List<SprintStory>();



        [JsonIgnore]
        public List<Task> Tasks { get; set; } = new List<Task>();
    }
}
