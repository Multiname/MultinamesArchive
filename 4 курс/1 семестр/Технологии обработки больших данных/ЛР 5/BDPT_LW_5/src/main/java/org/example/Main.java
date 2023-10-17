package org.example;

import org.apache.mahout.cf.taste.common.TasteException;
import org.apache.mahout.cf.taste.eval.RecommenderBuilder;
import org.apache.mahout.cf.taste.eval.RecommenderEvaluator;
import org.apache.mahout.cf.taste.impl.eval.AverageAbsoluteDifferenceRecommenderEvaluator;
import org.apache.mahout.cf.taste.impl.model.file.FileDataModel;
import org.apache.mahout.cf.taste.impl.recommender.*;
import org.apache.mahout.cf.taste.impl.recommender.slopeone.SlopeOneRecommender;
import org.apache.mahout.cf.taste.impl.similarity.*;
import org.apache.mahout.cf.taste.model.DataModel;
import org.apache.mahout.cf.taste.recommender.RecommendedItem;
import org.apache.mahout.cf.taste.recommender.Recommender;
import org.apache.mahout.cf.taste.similarity.ItemSimilarity;
import org.apache.mahout.cf.taste.similarity.UserSimilarity;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class Main {
    public static void main(String args[]) throws IOException, TasteException {
        File file = new File("D:\\movies.csv");
        FileReader fr = new FileReader(file);
        BufferedReader br = new BufferedReader(fr);

        Map<Long, String> movies = new HashMap<Long, String>();
        String line;
        while((line = br.readLine()) != null){
            movies.put(Long.parseLong(line.split(",")[0]), line);
        }

        DataModel model = new FileDataModel(new File("D:\\ratings.csv"));

//        UserSimilarity similarity_0 = new EuclideanDistanceSimilarity(model);
//        ClusterSimilarity clusterSimilarity_0 = new FarthestNeighborClusterSimilarity(similarity_0);
//        TreeClusteringRecommender recommender_0 = new TreeClusteringRecommender(model, clusterSimilarity_0, 600);
//        List<RecommendedItem> recommendations_0 = recommender_0.recommend(1, 1);
//        System.out.println("recommender: TreeClusteringRecommender");
//        System.out.println("similarity: EuclideanDistanceSimilarity");
//        System.out.println("clusterSimilarity: FarthestNeighborClusterSimilarity");
//        System.out.println();
//        for (RecommendedItem recommendation : recommendations_0) {
//            System.out.println(movies.get(recommendation.getItemID()));
//        }
//        System.out.println();

        ItemSimilarity similarity_1 = new EuclideanDistanceSimilarity(model);
        GenericItemBasedRecommender recommender_1 = new GenericItemBasedRecommender(model, similarity_1);
        List<RecommendedItem> recommendations_1 = recommender_1.recommend(1, 5);
        System.out.println("recommender: GenericItemBasedRecommender");
        System.out.println("similarity: EuclideanDistanceSimilarity");
        System.out.println();
        for (RecommendedItem recommendation : recommendations_1) {
            System.out.println(movies.get(recommendation.getItemID()));
        }
        System.out.println();

        ItemSimilarity similarity_2 = new PearsonCorrelationSimilarity(model);
        GenericItemBasedRecommender recommender_2 = new GenericItemBasedRecommender(model, similarity_2);
        List<RecommendedItem> recommendations_2 = recommender_2.recommend(1, 5);
        System.out.println("recommender: GenericItemBasedRecommender");
        System.out.println("similarity: PearsonCorrelationSimilarity");
        System.out.println();
        for (RecommendedItem recommendation : recommendations_2) {
            System.out.println(movies.get(recommendation.getItemID()));
        }
        System.out.println();

        SlopeOneRecommender recommender_3 = new SlopeOneRecommender(model);
        List<RecommendedItem> recommendations_3 = recommender_3.recommend(1, 5);
        System.out.println("recommender: SlopeOneRecommender");
        System.out.println();
        for (RecommendedItem recommendation : recommendations_3) {
            System.out.println(movies.get(recommendation.getItemID()));
        }
        System.out.println();

        RecommenderEvaluator evaluator = new AverageAbsoluteDifferenceRecommenderEvaluator();
        RecommenderBuilder builder_1 = new RecommenderBuilder() {
            @Override
            public Recommender buildRecommender(DataModel model) throws TasteException {
                ItemSimilarity similarity = new EuclideanDistanceSimilarity(model);
                return new GenericItemBasedRecommender (model, similarity);
            }
        };
        double score_1 = 0;
        for(int i = 0; i < 10; i++) {
            double value = evaluator.evaluate(builder_1, null, model, 0.7, 0.2);
            score_1 += value;
        }
        score_1 /= 10;
        System.out.println("GenericItemBasedRecommender, EuclideanDistanceSimilarity: " + score_1);

        RecommenderBuilder builder_2 = new RecommenderBuilder() {
            @Override
            public Recommender buildRecommender(DataModel model) throws TasteException {
                ItemSimilarity similarity = new PearsonCorrelationSimilarity(model);
                return new GenericItemBasedRecommender (model, similarity);
            }
        };
        double score_2 = 0;
        for(int i = 0; i < 10; i++) {
            double value = evaluator.evaluate(builder_2, null, model, 0.7, 0.2);
            score_2 += value;
        }
        score_2 /= 10;
        System.out.println("GenericItemBasedRecommender, PearsonCorrelationSimilarity: " + score_2);

        RecommenderBuilder builder_3 = new RecommenderBuilder() {
            @Override
            public Recommender buildRecommender(DataModel model) throws TasteException {
                return new SlopeOneRecommender(model);
            }
        };
        double score_3 = 0;
        for(int i = 0; i < 10; i++) {
            double value = evaluator.evaluate(builder_3, null, model, 0.7, 0.2);
            score_3 += value;
        }
        score_3 /= 10;
        System.out.println("SlopeOneRecommender: " + score_3);
    }
}
