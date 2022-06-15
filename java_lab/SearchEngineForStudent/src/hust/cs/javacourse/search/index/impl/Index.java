package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.*;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * AbstractIndex的具体实现类
 */
public class Index extends AbstractIndex {

    /**
     *  缺省构造函数,构建空索引
     */
    public Index() {
    }

    /**
     * 返回索引的字符串表示
     *
     * @return 索引的字符串表示
     */
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("docId-------docPath mapping :\n{\n");
        for (Map.Entry<Integer, String> entry : docIdToDocPathMapping.entrySet()) {
            builder.append(entry.getKey());
            builder.append("\t---->\t");
            builder.append(entry.getValue());
            builder.append("\n");
        }
        builder.append("}\nPostingList: \n{\n");
        for (Map.Entry<AbstractTerm, AbstractPostingList> entry : termToPostingListMapping.entrySet()) {
            builder.append(entry.getKey().toString());
            builder.append("\t---->\t");
            builder.append(entry.getValue().toString());
        }
        builder.append("}\n");
        return builder.toString();
    }

    /**
     * 添加文档到索引，更新索引内部的HashMap
     *
     * @param document ：文档的AbstractDocument子类型表示
     */
    @Override
    public void addDocument(AbstractDocument document) {
        docIdToDocPathMapping.put(document.getDocId(), document.getDocPath());
        for (AbstractTermTuple tuple : document.getTuples()) {
            // no term-key
            if (!termToPostingListMapping.containsKey(tuple.term)) {
                // new postingList and new posting
                List<Integer> positions = new ArrayList<>();
                positions.add(tuple.curPos);
                Posting posting = new Posting(document.getDocId(), tuple.freq, positions);
                // add postingList and posting
                termToPostingListMapping.put(tuple.term, new PostingList());
                termToPostingListMapping.get(tuple.term).add(posting);
            } else {
                // get existing term without the posting the postingList have
                int postingIndex = termToPostingListMapping.get(tuple.term).indexOf(document.getDocId());
                if (termToPostingListMapping.get(tuple.term).indexOf(document.getDocId()) == -1) {
                    List<Integer> positions = new ArrayList<>();
                    positions.add(tuple.curPos);
                    Posting posting = new Posting(document.getDocId(), tuple.freq, positions);
                    termToPostingListMapping.get(tuple.term).add(posting);
                } else {
                    // there has been the term and the posting with the same docId, now change the frequency and its positions
                    termToPostingListMapping.get(tuple.term).get(postingIndex).getPositions().add(tuple.curPos);
                    int curFreq = termToPostingListMapping.get(tuple.term).get(postingIndex).getFreq();
                    termToPostingListMapping.get(tuple.term).get(postingIndex).setFreq(curFreq + 1);
                }
            }
        }
    }

    /**
     * <pre>
     * 从索引文件里加载已经构建好的索引.内部调用FileSerializable接口方法readObject即可
     * @param file ：索引文件
     * </pre>
     */
    @Override
    public void load(File file) {
        try {
            readObject(new ObjectInputStream(new FileInputStream(file)));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * <pre>
     * 将在内存里构建好的索引写入到文件. 内部调用FileSerializable接口方法writeObject即可
     * @param file ：写入的目标索引文件
     * </pre>
     */
    @Override
    public void save(File file) {
        try {
            writeObject(new ObjectOutputStream(new FileOutputStream(file)));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 返回指定单词的PostingList
     *
     * @param term : 指定的单词
     * @return ：指定单词的PostingList;如果索引字典没有该单词，则返回null
     */
    @Override
    public AbstractPostingList search(AbstractTerm term) {
        // FIXME: I don't know if it will report an error if it doesn't exist search method, return the value corresponding to the specified key in the map
        AbstractPostingList abstractPostingList;
        try {
            abstractPostingList = termToPostingListMapping.get(term);
        } catch (NullPointerException | ClassCastException e) {
            e.printStackTrace();
            abstractPostingList = null;
        }
        return abstractPostingList;
        //return termToPostingListMapping.get(term);
    }

    /**
     * 返回索引的字典.字典为索引里所有单词的并集
     *
     * @return ：索引中Term列表
     */
    @Override
    public Set<AbstractTerm> getDictionary() {
        // FIXME: 不确定是不是对的, 返回keySet
        return termToPostingListMapping.keySet();
    }

    /**
     * <pre>
     * 对索引进行优化，包括：
     *      对索引里每个单词的PostingList按docId从小到大排序
     *      同时对每个Posting里的positions从小到大排序
     * 在内存中把索引构建完后执行该方法
     * </pre>
     */
    @Override
    public void optimize() {
        for (Map.Entry<AbstractTerm, AbstractPostingList> entry : termToPostingListMapping.entrySet()) {
            for (int i = 0; i < entry.getValue().size(); ++i) {
                // for each posting in the postingList, sort the existing positions of the term
                entry.getValue().get(i).sort();
            }
            // sort the posting in the postingList by docId
            entry.getValue().sort();
        }
    }

    /**
     * 根据docId获得对应文档的完全路径名
     *
     * @param docId ：文档id
     * @return : 对应文档的完全路径名
     */
    @Override
    public String getDocName(int docId) {
        return docIdToDocPathMapping.get(docId);
    }

    /**
     * 写到二进制文件
     *
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(docIdToDocPathMapping.size());
            out.writeObject(termToPostingListMapping.size());
            for (Map.Entry<Integer, String> entry : docIdToDocPathMapping.entrySet()) {
                out.writeObject(entry.getKey());
                out.writeObject(entry.getValue());
            }
            for (Map.Entry<AbstractTerm, AbstractPostingList> entry : termToPostingListMapping.entrySet()) {
                entry.getKey().writeObject(out);
                entry.getValue().writeObject(out);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 从二进制文件读
     *
     * @param in ：输入流对象
     */
    @Override
    public void readObject(ObjectInputStream in) {
        int docIdToDocPathMappingSize = 0;
        int termToPostingListMappingSize = 0;
        try {
            docIdToDocPathMappingSize = (Integer) in.readObject();
            termToPostingListMappingSize = (Integer) in.readObject();
            for (int i = 0; i < docIdToDocPathMappingSize; ++i) {
                int docId = (Integer) in.readObject();
                String docPath = (String) in.readObject();
                docIdToDocPathMapping.put(docId, docPath);
            }
            for (int i = 0; i < termToPostingListMappingSize; ++i) {
                AbstractTerm term = new Term();
                term.readObject(in);
                AbstractPostingList postingList = new PostingList();
                postingList.readObject(in);
                termToPostingListMapping.put(term, postingList);
            }
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * 将index以文本形式写入，默认位置为index.txt
     *
     * @param file : input file
     */
    public void writePlainText(File file){
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(file));
            // PrintWriter printWriter = new PrintWriter(writer);
            writer.write(this.toString());
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
