import org.apache.mahout.clustering.Cluster;
import org.apache.mahout.clustering.dirichlet.DirichletClusterer;
import org.apache.mahout.clustering.dirichlet.models.GaussianClusterDistribution;
import org.apache.mahout.common.distance.*;
import org.apache.mahout.math.DenseVector;
import org.apache.mahout.math.RandomAccessSparseVector;
import org.apache.mahout.math.Vector;
import org.apache.mahout.math.VectorWritable;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static double[][] readFile(String path) throws IOException {
        List<String> temp = new ArrayList<>();
        try(BufferedReader br = new BufferedReader(new FileReader(path)))
        {
            String s;
            while((s=br.readLine())!=null){
                temp.add(s);
            }
        }
        double[][] result = new double[temp.size()][2];
        for(int i = 0; i < temp.size(); i++){
            int sep_idx = temp.get(i).indexOf(',');
            result[i][0] = Double.parseDouble(temp.get(i).substring(0, sep_idx));
            result[i][1] = Double.parseDouble(temp.get(i).substring(sep_idx + 1));
        }
        return result;
    }

    public static List<Vector> getPoints(double[][] raw) {
        List<Vector> points = new ArrayList<>();
        for (double[] fr : raw) {
            Vector vec = new RandomAccessSparseVector(fr.length);
            vec.assign(fr);
            points.add(vec);
        }
        return points;
    }

    public static void main(String[] args) throws Exception {
        List<Vector> vectors = getPoints(readFile("/home/hadoop/points.txt"));

        List<VectorWritable> points = new ArrayList<>();
        for (Vector sd : vectors) {
            points.add(new VectorWritable(sd));
        }

        DirichletClusterer dc = new DirichletClusterer(points,
                new GaussianClusterDistribution(new VectorWritable(
                        new DenseVector(2))), 1.0, 2, 2, 6);
        List<Cluster[]> result = dc.cluster(20);
        List<Vector> centers = new ArrayList<>();
        for (Cluster cluster : result.get(result.size() - 1)) {
            centers.add(cluster.getCenter());
        }

        DistanceMeasure manhattanMeasure = new ManhattanDistanceMeasure();
        DistanceMeasure cosineMeasure = new CosineDistanceMeasure();

        FileWriter writer = new FileWriter("/home/hadoop/mаnhattanMeasure.txt", false);
        for(Vector vector : vectors){
            double minDistance = manhattanMeasure.distance(vector, centers.get(0));
            int minCenterId = 0;
            for(int i = 1; i < centers.size(); i++){
                if(minDistance > manhattanMeasure.distance(vector, centers.get(i))){
                    minDistance = manhattanMeasure.distance(vector, centers.get(i));
                    minCenterId = i;
                }
            }
            writer.write(vector.get(0) + ", " + vector.get(1) + " : " + minCenterId + "\n");
        }
        writer.flush();

        writer = new FileWriter("/home/hadoop/cоsineMeasure.txt", false);
        for(Vector vector : vectors){
            double minDistance = cosineMeasure.distance(vector, centers.get(0));
            int minCenterId = 0;
            for(int i = 1; i < centers.size(); i++){
                if(minDistance > cosineMeasure.distance(vector, centers.get(i))){
                    minDistance = cosineMeasure.distance(vector, centers.get(i));
                    minCenterId = i;
                }
            }
            writer.write(vector.get(0) + ", " + vector.get(1) + " : " + minCenterId + "\n");
        }
        writer.flush();
    }
}