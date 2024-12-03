#pragma once

#include "crypto/crypto.h"

namespace ots {
    class KeyStore {
        public:
            operator crypto::secret_key&() { return m_key; }
        protected:
            crypto::secret_key m_key;
    };
}
