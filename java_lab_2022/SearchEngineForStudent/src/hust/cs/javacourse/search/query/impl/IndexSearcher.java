package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.impl.Index;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;
import hust.cs.javacourse.search.util.Config;

import javax.net.ssl.HostnameVerifier;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;

/**
 * @author dong
 */
public class IndexSearcher extends AbstractIndexSearcher {

    /**
     * 从指定索引文件打开索引，加载到index对象里. 一定要先打开索引，才能执行search方法
     *
     * @param indexFile ：指定索引文件
     */
    @Override
    public void open(String indexFile) {
        this.index = new Index();
        index.load(new File(indexFile));
    }

    /**
     * 根据单个检索词进行搜索
     *
     * @param queryTerm ：检索词
     * @param sorter    ：排序器
     * @return ：命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm, Sort sorter) {
        // ignore case or not
        if (Config.IGNORE_CASE) {
            queryTerm.setContent(queryTerm.getContent().toLowerCase());
        }
        AbstractPostingList indexSearchResult = index.search(queryTerm);
        if (indexSearchResult == null) {
            return new Hit[0];
        }
        List<AbstractHit> result = new ArrayList<>();
        for (int i = 0; i < indexSearchResult.size(); i++) {
            AbstractPosting posting = indexSearchResult.get(i);

            AbstractHit hit = new Hit(posting.getDocId(), index.getDocName(posting.getDocId()));
            hit.getTermPostingMapping().put(queryTerm, posting);
            hit.setScore(sorter.score(hit));
            result.add(hit);
        }
        sorter.sort(result);
        AbstractHit[] ans = new AbstractHit[result.size()];
        return result.toArray(ans);
    }

    /**
     * 根据二个检索词进行搜索
     *
     * @param queryTerm1 ：第1个检索词
     * @param queryTerm2 ：第2个检索词
     * @param sorter     ：排序器
     * @param combine    ：多个检索词的逻辑组合方式
     * @return ：命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm1, AbstractTerm queryTerm2, Sort sorter, LogicalCombination combine) {
        AbstractPostingList postingList1 = index.search(queryTerm1);
        AbstractPostingList postingList2 = index.search(queryTerm2);
        // both of the postingList are null
        if (postingList1 == null && postingList2 == null) {
            return new Hit[0];
        }
        List<AbstractHit> abstractHits = new ArrayList<>();
        if (combine == LogicalCombination.OR) {
            // search another one if this one doesn't exist
            if (postingList1 == null) {
                return search(queryTerm2, sorter);
            }
            if (postingList2 == null) {
                return search(queryTerm1, sorter);
            }
            for (int i = 0; i < postingList1.size(); ++i) {
                int docId = postingList1.get(i).getDocId();
                AbstractHit hit = new Hit(docId, index.getDocName(docId));
                hit.getTermPostingMapping().put(queryTerm1, postingList1.get(i));
                // find posting index in the other postingList with the same docId
                int index2 = postingList2.indexOf(docId);
                if (index2 != -1) {
                    // there is a posting in the postingList2
                    hit.getTermPostingMapping().put(queryTerm2, postingList2.get(index2));
                }
                hit.setScore(sorter.score(hit));
                abstractHits.add(hit);
            }
            for (int i = 0; i < postingList2.size(); ++i) {
                int docId = postingList2.get(i).getDocId();
                int index1 = postingList1.indexOf(docId);
                if (index1 == -1) {
                    // add hit if it does not exist in postingList1
                    AbstractHit hit = new Hit(docId, index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm2, postingList2.get(i));
                    hit.setScore(sorter.score(hit));
                    abstractHits.add(hit);
                }
            }
        } else if (combine == LogicalCombination.AND) {
            // Not null
            if (postingList1 == null || postingList2 == null) {
                return new Hit[0];
            }
            for (int i = 0; i < postingList1.size(); ++i) {
                int docId = postingList1.get(i).getDocId();
                int index2 = postingList2.indexOf(docId);
                if (index2 != -1) {
                    AbstractHit hit = new Hit(docId, index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm1, postingList1.get(i));
                    hit.getTermPostingMapping().put(queryTerm2, postingList2.get(index2));
                    hit.setScore(sorter.score(hit));
                    abstractHits.add(hit);
                }
            }
        }
        sorter.sort(abstractHits);
         AbstractHit[] returnResult = new AbstractHit[abstractHits.size()];
         return abstractHits.toArray(returnResult);
//        return abstractHits.toArray(new AbstractHit[0]);
    }
}
