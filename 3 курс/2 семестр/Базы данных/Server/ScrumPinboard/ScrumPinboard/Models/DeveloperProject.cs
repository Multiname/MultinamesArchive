using System.ComponentModel.DataAnnotations.Schema;
using System.Text.Json.Serialization;

namespace ScrumPinboard.Models
{
    [Table("developers_projects")]
    public class DeveloperProject
    {
        [JsonIgnore]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        [Column("id")]
        public int Id { get; set; }

        [Column("developer_id")]
        public int DeveloperId { get; set; }

        [Column("project_id")]
        public int ProjectId { get; set; }

        [Column("is_owner")]
        public bool IsOwner { get; set; }



        [JsonIgnore]
        public Developer Developer { get; set; }

        [JsonIgnore]
        public Project Project { get; set; }
    }
}
