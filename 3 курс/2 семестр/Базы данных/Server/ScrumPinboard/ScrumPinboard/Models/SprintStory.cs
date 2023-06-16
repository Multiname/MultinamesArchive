using System.ComponentModel.DataAnnotations.Schema;
using System.Text.Json.Serialization;

namespace ScrumPinboard.Models
{
    [Table("sprints_stories")]
    public class SprintStory
    {
        public enum ProcessState
        {
            TODO,
            REJECTED,
            IN_PROGRESS,
            READY_FOR_TESTING,
            DONE
        }



        [JsonIgnore]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        [Column("id")]
        public int Id { get; set; }

        [Column("sprint_id")]
        public int SprintId { get; set; }

        [Column("story_id")]
        public int StoryId { get; set; }

        [Column("state")]
        public ProcessState State { get; set; }



        [JsonIgnore]
        public Sprint Sprint { get; set; }

        [JsonIgnore]
        public Story Story { get; set; }
    }
}
