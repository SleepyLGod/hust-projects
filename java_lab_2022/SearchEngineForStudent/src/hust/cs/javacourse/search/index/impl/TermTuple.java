package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;

import java.util.Objects;

/**
 * <pre>
 * AbstractTermTuple的具体实现类
 * AbstractTermTuple是所有TermTuple对象的抽象父类.
 *      一个TermTuple对象为三元组(单词，出现频率，出现的当前位置).
 *      当解析一个文档时，每解析到一个单词，应该产生一个三元组，其中freq始终为1(因为单词出现了一次).
 * </pre>
 *
 * @author dong
 */
public class TermTuple extends AbstractTermTuple {

    /**
     * 判断二个三元组内容是否相同
     *
     * @param obj ：要比较的另外一个三元组
     * @return 如果内容相等（三个属性内容都相等）返回true，否则返回false
     */
    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof TermTuple)) {
            return false;
        } else {
            return this.curPos == ((TermTuple) obj).curPos && Objects.equals(this.term, ((TermTuple) obj).term);
        }
    }

    /**
     * 获得三元组的字符串表示
     *
     * @return ： 三元组的字符串表示
     */
    @Override
    public String toString() {
        return "{\n" + " Term: " + term + ";\n CurPos: " + curPos + ";\n Freq: " + freq + ";\n}\n";
    }
}
