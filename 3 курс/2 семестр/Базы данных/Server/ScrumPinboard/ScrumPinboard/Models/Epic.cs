using System.ComponentModel.DataAnnotations.Schema;
using System.Text.Json.Serialization;

namespace ScrumPinboard.Models
{
    [Table("epics")]
    public class Epic
    {
        public enum Priority
        {
            MINOR,
            LOW,
            MEDIUM,
            HIGH,
            MAJOR
        }



        [JsonIgnore]
        [Column("id")]
        public int Id { get; set; }

        [Column("name")]
        public string Name { get; set; } = "";

        [Column("project_id")]
        public int ProjectId { get; set; }
        
        [Column("priority")]
        public Priority EpicPriority { get; set; }

        [Column("is_done")]
        public bool IsDone { get; set; }



        [JsonIgnore]
        public Project Project { get; set; } = new Project();



        [JsonIgnore]
        public List<Story> Stories { get; set; } = new List<Story>();
    }
}
