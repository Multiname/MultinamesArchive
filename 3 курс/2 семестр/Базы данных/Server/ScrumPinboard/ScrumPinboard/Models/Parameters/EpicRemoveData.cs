namespace ScrumPinboard.Models.Parameters
{
    public class EpicRemoveData
    {
        public int EpicId { get; set; }

        public EpicRemoveData(int epicId)
        {
            EpicId = epicId;
        }
    }
}
