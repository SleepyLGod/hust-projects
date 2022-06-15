package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.StopWords;

import java.io.IOException;
import java.util.Arrays;
import java.util.List;

/**
 * <pre>
 * 抽象类AbstractTermTupleFilter的具体子类,里面包含另一个AbstractTermTupleStream对象作为输入
 * 并对输入的AbstractTermTupleStream进行过滤,例如过滤掉所有停用词（the，is are...)对应的三元组
 *
 * 通过StopWords类中的STOP_WORDS字段来判断是否是停用词，如果是则丢弃，不是则保留
 * </pre>
 *
 * @author dong
 */
public class StopWordTermTupleFilter extends AbstractTermTupleFilter {

    /**
     * 构造函数
     *
     * @param input ：Filter的输入，类型为AbstractTermTupleStream
     */
    public StopWordTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
    }

    /**
     * 获得下一个三元组
     *
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() throws IOException {
        AbstractTermTuple tuple = input.next();
        if (tuple != null) {
            List<String> wordArrayList = Arrays.asList(StopWords.STOP_WORDS);
            while (wordArrayList.contains(tuple.term.getContent())) {
                tuple = input.next();
                if (tuple == null) {
                    return null;
                }
            }
            return tuple;
        } else {
            return null;
        }
    }
}
