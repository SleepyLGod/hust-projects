# encoding:GBK

import uncompressor  # import uncompressor��ʱ�����Զ�ִ��import uncompressor�������__init__.py
import fileutil
import parse
import exception
import logger
import shell
import autotest
import os
import excelutil

# ѧ���ύ�ĵ��ĸ�Ŀ¼ ����Ҫ����ʵ�����л�����������
# ��Ŀ¼�°���ѧ���ύ��ѹ���ļ���ѹ���ļ�������ѭ�������淶
# submit_root_dir = r'E:\JavaExperimentTest\18'
# submit_root_dir = r'C:\Users\86156\Desktop\JavaExperiment\Experiment1Test'
submit_root_dir = r'.'

if submit_root_dir[-1] != '\\':
    submit_root_dir += '\\'

# ��ѹ��Ŀ��Ŀ¼
uncompress_test_target = submit_root_dir + r'temp'
if not os.path.exists(uncompress_test_target):
    os.mkdir(uncompress_test_target)

# ���в��Ե�Ŀ¼, ��ѹ���ѧ������Ŀ¼���ݿ�����������ѧ������·���������ĵ�����
running_test_dir = submit_root_dir + r'run'
if not os.path.exists(running_test_dir):
    os.mkdir(running_test_dir)


# ��־Ŀ¼
logger_path = submit_root_dir + r'logs'
if not os.path.exists(logger_path):
    os.mkdir(logger_path)

# ȫ�ֵ�logger
run_logger = logger.Logger('run logger', logger_path).get_logger()

# �Ƿ���Ҫ�����Խ��д��Excel,�������ΪFalse, ���������ȫ�ֱ���original_score_excel_file��test_score_excel_file��Ч
# �����ѧ���Լ����У�����ΪFalse
record_test_result_to_excel = False

# ԭʼ�ɼ����ص�
# original_score_excel_file = submit_root_dir + r'JAVA ���Գ������(18���ۺϼ��ص�����).xlsx'
original_score_excel_file = submit_root_dir + r'JAVA ���Գ������ʵ��(20��ʵ����ۺϼ��ص�).xlsx'

# �Զ����Խ�����ص����������Ȳ�����
# test_score_excel_file = submit_root_dir + r'JAVA ���Գ������(18���ۺϼ��ص�����)-ʵ����Խ��.xlsx'
test_score_excel_file = submit_root_dir + r'JAVA ���Գ������ʵ��(20��ʵ����ۺϼ��ص�)-ʵ����Խ��.xlsx'

if record_test_result_to_excel:
    excel = excelutil.Excel(original_score_excel_file, test_score_excel_file)  # ����Excel�ļ� original_score_excel_file


def find_all_submit_files(root_dir):
    """
    ����ָ��Ŀ¼������ѧ���ύ���ĵ�
    :param root_dir: ָ��Ŀ¼
    :return: ѧ���ύ���ĵ��б�
    """
    li = []
    submit_files = fileutil.find_files(submit_root_dir)
    for f in submit_files:
        f_suffix = fileutil.find_file_suffix(f)  # �õ�f�ĺ�׺
        if f_suffix == '.zip' or f_suffix == '.rar':
            li.append(f)

    return li


def handle_per_compressed_file(compressed_file):
    """
    ����ÿ��ѧ���ύ��ѹ���ļ�
    :param compressed_file: ѧ���ύ��ѹ���ļ�����ȫ·��
    :return:
    """
    global student_index_excel
    run_logger.info('---->����' + compressed_file + '�µ�ѧ������')

    # �õ�������׺��ѹ���ļ���
    file_name_without_suffix = fileutil.find_file_name_without_suffix(compressed_file)
    # ��ѹ���ļ�������ѧ����Ϣ
    try:
        sinfo = parse.parse_student_info(file_name_without_suffix)
    except exception.FileNameFormatError as e:
        run_logger.error('-------->' + e)
        return  # ���ѧ����Ϣ��������, ֱ�ӷ��أ�������һ������

    if record_test_result_to_excel:
        student_index_excel = excel.find_student(0, sinfo)  # ���Ҹ�ѧ���Ƿ���Excel��
        if student_index_excel == -1:
            run_logger.warning('-------->ѧ����Ϣ:ѧ��=' + sinfo.s_id + ',�༶=' + sinfo.s_class + ',����=' + sinfo.s_name + '��ѧ�����ڻ�������')
            return  # �����ѧ������Excel��ֱ�ӷ��ز�����

    run_logger.info('-------->ѧ����Ϣ:ѧ��=' + sinfo.s_id + ',�༶=' + sinfo.s_class + ',����=' + sinfo.s_name)

    # ��ѹѧ���ļ�
    fileutil.remove_subdir(uncompress_test_target)  # ������ս�ѹ��Ŀ��Ŀ¼
    try:
        uncompressor.decompression(compressed_file, uncompress_test_target)
        run_logger.info('-------->��ѹ' + compressed_file + '��Ŀ���ļ���' + uncompress_test_target)
    except Exception as e:
        run_logger.error('-------->' + e.__str__())
        return  # �����ѹ����, ֱ�ӷ��أ�������һ������

    # �ҵ���ѹ��ѧ��������Զ�����Ŀ¼
    run_logger.info('---------------->��ʼ����ѧ��=' + sinfo.s_id + ',�༶=' + sinfo.s_class + ',����=' + sinfo.s_name + '�Ĵ���')
    test_dir = parse.find_test_dir(uncompress_test_target)  # �ҵ���ѹ��ѧ��������Զ�����Ŀ¼
    if test_dir == '':
        run_logger.error('---------------->ѧ��=' + sinfo.s_id + ',�༶=' + sinfo.s_class + ',����=' + sinfo.s_name + '���Զ�����Ŀ¼�����ڻ��ߴ�������')
        if record_test_result_to_excel:
            # ��Excel���¼�����Ĳ�������
            excel.write_cell_in_dataframe(0, student_index_excel, excelutil.sheet0_auto_test_detail_excel_col_index, '�Զ�����Ŀ¼�����ڻ��ߴ�������')
        return  # ����Ҳ�������Ŀ¼����ֱ�ӷ��أ�������һ������

    # �����Զ�����Ŀ¼test_dir�����ݵ����в��Ե�Ŀ¼running_test_dir
    fileutil.remove_subdir(running_test_dir)  # ��������в��Ե�Ŀ¼running_test_dir
    fileutil.copy_dir(test_dir, running_test_dir)

    # ��ʼ����running_test_dir����Ĵ���
    # test_executor = autotest.TestExecutor(test_dir)
    test_executor = autotest.TestExecutor(running_test_dir)
    result = test_executor.run_test()
    if result.code != 0:
        # �����Թ����еĴ���д���ѧ������־�ļ�
        student_error_log_file = sinfo.s_id + '_' + sinfo.s_class + '_' + sinfo.s_name + '_error.log'
        student_error_log_file_full_path = os.path.join(logger_path, student_error_log_file)
        fileutil.write_to_file(student_error_log_file_full_path, result.error)


        student_out_log_file = sinfo.s_id + '_' + sinfo.s_class + '_' + sinfo.s_name + '_out.log'
        student_out_log_file_full_path = os.path.join(logger_path, student_out_log_file)
        fileutil.write_to_file(student_out_log_file_full_path, result.out)

        run_logger.error('---------------->ѧ��=' + sinfo.s_id + ',�༶=' + sinfo.s_class + ',����=' + sinfo.s_name + '���Զ����Դ�������,��鿴�ļ�' +
                         student_error_log_file_full_path + '��' + student_out_log_file_full_path)


    final_result = test_executor.parse_final_result(result)
    if final_result is None:
        run_logger.error('---------------->ѧ��=' + sinfo.s_id + ',�༶=' + sinfo.s_class + ',����=' + sinfo.s_name + '�Ĵ������û�еõ����ղ��Խ��')
        if record_test_result_to_excel:
            # ��Excel���¼�����Ĳ�������
            excel.write_cell_in_dataframe(0, student_index_excel, excelutil.sheet0_auto_test_detail_excel_col_index, '�������û�еõ����ղ��Խ��')
    else:
        run_logger.info('---------------->ѧ��=' + sinfo.s_id + ',�༶=' + sinfo.s_class + ',����=' + sinfo.s_name +
                        '�Ĵ�����Խ��Ϊ����������=' + str(final_result[0]) + ',ʧ�ܸ���=' + str(final_result[1]) + ',���Ը���=' + str(final_result[2]))
        if record_test_result_to_excel:
            # ��Excel���¼�����Ĳ�������
            record_info = str(final_result[0]) + '-' + str(final_result[1]) + '-' + str(final_result[2])
            excel.write_cell_in_dataframe(0, student_index_excel, excelutil.sheet0_auto_test_detail_excel_col_index, record_info)

    None

def run_auto_test():
    run_logger.info('��ʼ�Զ�����' + submit_root_dir + '�µ�����ѧ������')

    # ��������ѧ���ύ��ѹ���ĵ��б�
    compressed_file_list = find_all_submit_files(submit_root_dir)
    # print(compressed_file_list)

    # ����ÿ��ѧ����ѹ���ĵ�
    for file in compressed_file_list:
        handle_per_compressed_file(file)

    run_logger.info('�������')
    if record_test_result_to_excel:
        excel.save_to_new_excel(0)

    None

if __name__ == "__main__":
    run_auto_test()
