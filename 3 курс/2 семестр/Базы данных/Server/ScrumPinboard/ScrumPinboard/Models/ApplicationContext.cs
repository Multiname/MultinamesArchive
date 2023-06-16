using Microsoft.EntityFrameworkCore;
using Npgsql;

namespace ScrumPinboard.Models
{
    public class ApplicationContext : DbContext
    {
        public DbSet<Developer> Developers { get; set; } = null!;
        public DbSet<DeveloperProject> DevelopersProjects { get; set; } = null!;
        public DbSet<Project> Projects { get; set; } = null!;
        public DbSet<Epic> Epics { get; set; } = null!;
        public DbSet<Story> Stories { get; set; } = null!;
        public DbSet<Task> Tasks { get; set; } = null!;
        public DbSet<SprintStory> SprintsStories { get; set; } = null!;
        public DbSet<Sprint> Sprints { get; set; }

        public ApplicationContext()
        {
            AppContext.SetSwitch("Npgsql.EnableLegacyTimestampBehavior", true);

            NpgsqlConnection.GlobalTypeMapper.MapEnum<Epic.Priority>();
            NpgsqlConnection.GlobalTypeMapper.MapEnum<SprintStory.ProcessState>();

            Database.EnsureCreated();
        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.EnableSensitiveDataLogging();

            var configuration = new ConfigurationBuilder().AddJsonFile("appsettings.json").AddEnvironmentVariables().Build();

            optionsBuilder.UseNpgsql(configuration.GetConnectionString("DefaultConnection"));
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder
                .Entity<Developer>()
                .HasMany(x => x.Projects)
                .WithMany(x => x.Developers)
                .UsingEntity<DeveloperProject>(
                    x => x
                        .HasOne(y => y.Project)
                        .WithMany(y => y.DevelopersProjects)
                        .HasForeignKey(y => y.ProjectId),
                    x => x
                        .HasOne(y => y.Developer)
                        .WithMany(y => y.DevelopersProjects)
                        .HasForeignKey(y => y.DeveloperId),
                    x =>
                    {
                        x.HasKey(y => new { y.ProjectId, y.DeveloperId });
                        x.ToTable("developers_projects");
                    }
                );

            modelBuilder
                .Entity<Sprint>()
                .HasMany(x => x.Stories)
                .WithMany(x => x.Sprints)
                .UsingEntity<SprintStory>(
                    x => x
                        .HasOne(y => y.Story)
                        .WithMany(y => y.SprintsStories)
                        .HasForeignKey(y => y.StoryId),
                    x => x
                        .HasOne(y => y.Sprint)
                        .WithMany(y => y.SprintsStories)
                        .HasForeignKey(y => y.SprintId),
                    x =>
                    {
                        x.HasKey(y => new { y.StoryId, y.SprintId });
                        x.ToTable("sprints_stories");
                    }
                );
        }
    }
}
