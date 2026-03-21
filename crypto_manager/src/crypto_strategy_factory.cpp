/// @file
/// @brief Определение фабрики криптографических стратегий.
/// @author Artemenko Anton

#include <crypto_strategy_factory.hpp>
#include <src/openssl_crypto_strategy.hpp>

std::unique_ptr<crypto_manager::ICryptoStrategy> crypto_manager::CreateCryptoStrategy(const CryptoBackend backend)
{
    switch (backend)
    {
        case CryptoBackend::OpenSsl:
            return std::make_unique<OpenSslCryptoStrategy>();
    }

    return nullptr;
}

std::unique_ptr<crypto_manager::ICryptoStrategy> crypto_manager::CreateCryptoStrategy()
{
    return CreateCryptoStrategy(CryptoBackend::OpenSsl);
}
