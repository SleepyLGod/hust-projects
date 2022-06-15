package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.*;

/**
 * <pre>
 *     AbstractTermTupleScanner是AbstractTermTupleStream的抽象子类，即一个具体的TermTupleScanner对象就是
 *     一个AbstractTermTupleStream流对象，它利用java.io.BufferedReader去读取文本文件得到一个个三元组TermTuple.
 *     其具体子类需要重新实现next方法获得文本文件里的三元组
 * </pre>
 * @author dong
 */
public class TermTupleScanner extends AbstractTermTupleScanner {

    /**
     * 缺省构造函数
     */
    public TermTupleScanner() {
    }

    /**
     * 构造函数
     * @param input：指定输入流对象，应该关联到一个文本文件
     */
    public TermTupleScanner(BufferedReader input) {
        super(input);
    }

    /**
     * Cache redundant data for each row
     */
    Deque<AbstractTermTuple> queue = new LinkedList<>();

    /**
     * current position of the term
     */
    int thisCurPos = 0;

    /**
     * 获得下一个三元组
     *
     * @return: 下一个三元组；如果到了流的末尾，返回null
     */
    @Override
    public AbstractTermTuple next() throws IOException {
        if (queue.isEmpty()) {
            String inputString = input.readLine();
            if (inputString == null) {
                // input over
                return null;
            }
            // keep reading until a non-blank line or the end of the file is encountered
            while (inputString.trim().length() == 0) {
                inputString = input.readLine();
                if (inputString == null) {
                    return null;
                }
            }
            StringSplitter splitter = new StringSplitter();
            splitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
            List<String> words = splitter.splitByRegex(inputString);
            for (String thisWord : words) {
                TermTuple termTuple = new TermTuple();
                termTuple.curPos = thisCurPos;
                termTuple.term = (Config.IGNORE_CASE) ? new Term(thisWord.toLowerCase()) : new Term(thisWord);
                queue.offerLast(termTuple);
                thisCurPos++;
            }
        }
        return queue.pollFirst();
    }
}
