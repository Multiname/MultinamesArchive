using System.ComponentModel.DataAnnotations.Schema;
using System.Text.Json.Serialization;

namespace ScrumPinboard.Models
{
    [Table("tasks")]
    public class Task
    {
        [JsonIgnore]
        [Column("id")]
        public int Id { get; set; }

        [Column("name")]
        public string Name { get; set; } = "";

        [Column("story_id")]
        public int StoryId { get; set; }

        [Column("estimated_hours")]
        public int EstimatedHours { get; set; }

        [Column("is_done")]
        public bool IsDone { get; set; }



        [JsonIgnore]
        public Story Story { get; set; } = new Story();
    }
}
