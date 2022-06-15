package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.parse.impl.*;

import java.io.*;
import java.util.Objects;

/**
 * <pre>
 * DocumentBuilder是Document构造器的具体子类.
 *      Document构造器的功能应该是由解析文本文档得到的TermTupleStream，产生Document对象.
 *  主要实现了父类的两个重载build方法
 * </pre>
 *
 * @author dong
 */
public class DocumentBuilder extends AbstractDocumentBuilder {

    /**
     * <pre>
     * 由解析文本文档得到的TermTupleStream,构造Document对象.
     * @param docId             : 文档id
     * @param docPath           : 文档绝对路径
     * @param termTupleStream   : 文档对应的TermTupleStream
     * @return ：Document对象
     * </pre>
     */
    @Override
    public AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream) throws IOException {
        AbstractDocument abstractDocument = new Document(docId, docPath);
        AbstractTermTuple abstractTermTuple = termTupleStream.next();
        while (abstractTermTuple != null) {
            abstractDocument.addTuple(abstractTermTuple);
            abstractTermTuple = termTupleStream.next();
        }
        termTupleStream.close();
        return abstractDocument;
    }

    /**
     * <pre>
     * 由给定的File,构造Document对象.
     * 该方法利用输入参数file构造出AbstractTermTupleStream子类对象后,内部调用
     *      AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream)
     * @param docId     : 文档id
     * @param docPath   : 文档绝对路径
     * @param file      : 文档对应File对象
     * @return          : Document对象
     * </pre>
     */
    @Override
    public AbstractDocument build(int docId, String docPath, File file) {
        AbstractDocument abstractDocument = null;
        AbstractTermTupleStream termTupleStream = null;
        try {
            termTupleStream = new TermTupleScanner(new BufferedReader(new InputStreamReader(new FileInputStream(file))));
            termTupleStream = new StopWordTermTupleFilter(termTupleStream);
            termTupleStream = new PatternTermTupleFilter(termTupleStream);
            termTupleStream = new LengthTermTupleFilter(termTupleStream);
            abstractDocument = build(docId, docPath, termTupleStream);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            Objects.requireNonNull(termTupleStream).close();
        }
        return abstractDocument;
    }
}
