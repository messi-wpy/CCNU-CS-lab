import smtplib
from email.mime.text import MIMEText
from email.header import Header
from email.utils import parseaddr, formataddr


def _format_addr(s):
    name, addr = parseaddr(s)
    return formataddr(Header(name, 'utf-8').encode(), addr)


from_address = "lp-wpy@qq.com"
password = '*******'
to_addr = "lp-wpy@qq.com"
smtp_server = 'smtp.qq.com'

msg = MIMEText("请更新每日进度.", 'plain', 'utf-8')

msg['From'] = formataddr((Header('wpy-lp', 'utf-8').encode(), from_address))
msg['To'] = formataddr((Header('管理员', 'utf-8').encode(), to_addr))
msg['Subject'] = Header("催更进度", 'utf-8').encode()

server = smtplib.SMTP(smtp_server, 25)
server.set_debuglevel(1)
server.login(from_address, password)
# to_addr是个list, 可以设置多个
server.sendmail(from_address, [to_addr], msg.as_string())
server.quit()
