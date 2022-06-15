package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.util.FileUtil;

import java.util.Map;
import java.util.ServiceConfigurationError;

/**
 * @author dong
 */
public class Hit extends AbstractHit {

    /**
     * 默认构造函数
     */
    public Hit() {
    }

    /**
     * 构造函数
     * @param docId     : 文档id
     * @param docPath   : 文档绝对路径
     */
    public Hit(int docId, String docPath) {
        super(docId, docPath);
    }

    /**
     * 构造函数
     * @param docId     : 文档id
     * @param docPath   : 文档绝对路径
     * @param termPostingMapping : 提供的termPostingMapping参数
     */
    public Hit(int docId, String docPath, Map<AbstractTerm, AbstractPosting> termPostingMapping) {
        super(docId, docPath, termPostingMapping);
    }

    /**
     * 获得文档id
     *
     * @return ： 文档id
     */
    @Override
    public int getDocId() {
        return this.docId;
    }

    /**
     * 获得文档绝对路径
     *
     * @return ：文档绝对路径
     */
    @Override
    public String getDocPath() {
        return this.docPath;
    }

    /**
     * 获得文档内容
     *
     * @return ： 文档内容
     */
    @Override
    public String getContent() {
        return this.content;
    }

    /**
     * 设置文档内容
     *
     * @param content ：文档内容
     */
    @Override
    public void setContent(String content) {
        this.content = content;
    }

    /**
     * 获得文档得分
     *
     * @return ： 文档得分
     */
    @Override
    public double getScore() {
        return this.score;
    }

    /**
     * 设置文档得分
     *
     * @param score ：文档得分
     */
    @Override
    public void setScore(double score) {
        this.score = score;
    }

    /**
     * 获得命中的单词和对应的Posting键值对
     *
     * @return ：命中的单词和对应的Posting键值对
     */
    @Override
    public Map<AbstractTerm, AbstractPosting> getTermPostingMapping() {
        return this.termPostingMapping;
    }

    /**
     * 获得命中结果的字符串表示, 用于显示搜索结果.
     *
     * @return : 命中结果的字符串表示
     */
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("\n-----------------------------------------\n")
                .append("docId: ").append(docId).append(";\ndocPath: ").append(docPath)
                .append(";\ncontent: ").append(content).append(";\nscore: ").append(score).append(";\n");
        for (Map.Entry<AbstractTerm, AbstractPosting> entry : termPostingMapping.entrySet()) {
            builder.append(entry.getKey().getContent()).append("\t----->\t").append(entry.getValue()).append("\n");
        }
        return builder.toString();
    }

    /**
     * 比较二个命中结果的大小，根据score比较
     *
     * @param o ：要比较的名字结果
     * @return ：二个命中结果得分的差值
     */
    @Override
    public int compareTo(AbstractHit o) {
        return (int) (getScore() - o.getScore());
    }
}
