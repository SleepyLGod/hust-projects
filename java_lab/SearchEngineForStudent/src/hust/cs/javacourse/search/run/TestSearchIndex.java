package hust.cs.javacourse.search.run;

import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;
import hust.cs.javacourse.search.query.impl.IndexSearcher;
import hust.cs.javacourse.search.query.impl.SimpleSorter;
import hust.cs.javacourse.search.util.Config;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

/**
 * 测试搜索
 * @author dong
 */
public class TestSearchIndex {

    /**
     *  搜索程序入口
     * @param args ：命令行参数
     */
    public static void main(String[] args) {
        Sort simpleSorter = new SimpleSorter();
        String indexFile = Config.INDEX_DIR + "index.dat";
        String searchResultTargetFile = Config.INDEX_DIR + "search_result.txt";
        AbstractIndexSearcher searcher = new IndexSearcher();
        searcher.open(indexFile);
        AbstractHit[] hits = searcher.search(new Term("government"), simpleSorter);
        // save the results
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(new File(searchResultTargetFile)));
            for(AbstractHit hit : hits) {
                System.out.println(hit);
                writer.write(hit.toString());
            }
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
