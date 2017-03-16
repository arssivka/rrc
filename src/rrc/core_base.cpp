/**
 *  @autor arssivka
 *  @date 3/16/17
 */

#include <rrc/core_base.h>


rrc::core_base::core_base(rrc::abstract_launcher& launcher, int argc, char** argv)
        : m_launcher(launcher) {
    m_args.assign(argv + 1, argv + argc);
}


const std::vector<std::string>& rrc::core_base::args() const noexcept {
    return m_args;
}


bool rrc::core_base::is_multithreaded() const {
    return m_launcher.is_multithreading();
}


void rrc::core_base::stop() {
    m_launcher.stop();
}
