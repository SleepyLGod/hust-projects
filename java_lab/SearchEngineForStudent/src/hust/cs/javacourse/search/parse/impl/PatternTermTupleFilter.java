package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StopWords;

import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Pattern;

/**
 * <pre>
 * 抽象类AbstractTermTupleFilter的具体子类,里面包含另一个AbstractTermTupleStream对象作为输入
 * 并对输入的AbstractTermTupleStream进行过滤,例如过滤掉所有停用词（the，is are...)对应的三元组
 *
 * 通过Config中的TERM_FILTER_PATTERN，进行正则匹配，符合则保留，不符合则丢弃
 * </pre>
 *
 * @author dong
 */
public class PatternTermTupleFilter extends AbstractTermTupleFilter {

    /**
     * 构造函数
     *
     * @param input ：Filter的输入，类型为AbstractTermTupleStream
     */
    public PatternTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
    }

    /**
     * 获得下一个三元组
     *
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() throws IOException {
        AbstractTermTuple termTuple = input.next();
        if (termTuple == null) {
            return null;
        }
        while (!termTuple.term.getContent().matches(Config.TERM_FILTER_PATTERN)) {
            termTuple = input.next();
            if (termTuple == null) {
                return null;
            }
        }
        return termTuple;
    }
}
